#include <algorithm>

#include "../../../include/core/canvas/Canvas.hpp"
#include "../../../include/domain/shapes/adapter/composite/CompositeShape.hpp"
#include "../../../include/patterns/state/concrete/modification/color/ChangeColorShapeState.hpp"
#include "../../../include/patterns/state/concrete/creation/AddShapeState.hpp"
#include "../../../include/patterns/state/concrete/modification/style/ChangeThicknessShapeState.hpp"
#include "../../../include/patterns/state/concrete/moving/DragState.hpp"

Canvas::Canvas(unsigned int width, unsigned int height, const std::string &title)
    : m_window(sf::VideoMode({width, height}), title), m_panel(m_window, [this](std::unique_ptr<IToolState> tool)

                                                               { this->SetTool(std::move(tool)); })
{
    m_window.setFramerateLimit(canvas::FRAME_RATE);
}

bool Canvas::IsOpen() const
{
    return m_window.isOpen();
}

void Canvas::Draw()
{
    while (IsOpen())
    {
        if (!HandleEvents())
        {
            break;
        }
        if (!Render())
        {
            break;
        }
    }
}

void Canvas::AddShape(std::shared_ptr<IDrawableShape> shape)
{
    m_shapes.push_back(std::move(shape));
}

bool Canvas::RemoveShape(const std::shared_ptr<IDrawableShape> &shape)
{
    unsigned id = shape->GetId();

    auto matchId = [&](const auto &s)

    { return s->GetId() == id; };

    m_shapes.erase(std::remove_if(m_shapes.begin(), m_shapes.end(), matchId), m_shapes.end());
    m_selected.erase(std::remove_if(m_selected.begin(), m_selected.end(), matchId), m_selected.end());

    return true;
}

void Canvas::ClearShapes()
{
    m_shapes.clear();
}

sf::Vector2f Canvas::GetMousePosition() const
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);

    return m_window.mapPixelToCoords(pixelPos);
}

bool Canvas::HandleEvents()
{
    while (auto event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
            return false;
        }

        SetEvent(*event);
        SelectEvent();

        m_panel.HandleMouseEvent(*event);

        UndoState();
        SaveState();

        if (m_tool)
        {
            m_tool->HandleEvent(this);

            bool isPersistentTool = dynamic_cast<DragState *>(m_tool.get()) != nullptr;

            if (!m_panel.IsDragMode() && !isPersistentTool)
            {
                SetTool(nullptr);
            }
        }
    }

    return true;
}

void Canvas::UndoState()
{
    if (auto event = GetEvent(); event.has_value())
    {
        sf::Event ev = event.value();

        if (auto keyPress = ev.getIf<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && !cmds.empty())
        {
            auto cmd = std::move(cmds.back());
            cmds.pop_back();

            ClearSelected();
            cmd->Undo();
        }
    }
}

void Canvas::SaveState()
{
    if (auto event = GetEvent(); event.has_value())
    {
        sf::Event ev = event.value();

        if (auto keyPress = ev.getIf<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
            {
                BinaryShapeStrategy s;
                SaveToFile(input::BIN_FILENAME, s);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
            {
                TxtShapeStrategy s;
                SaveToFile(input::TEXT_FILENAME, s);
            }
        }
    }
}

void Canvas::SelectEvent()
{
    if (auto event = GetEvent(); event.has_value())
    {
        sf::Event ev = event.value();

        if (auto mouseRelease = ev.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseRelease->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f clickPos = GetMousePosition();

                bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
                auto hit = HitTest(clickPos);

                const sf::Vector2f panelSize = m_panel.GetPanelSize();

                if (clickPos.y <= panelSize.y)
                {
                    return;
                }

                if (hit)
                {
                    if (!shift)
                    {
                        ClearSelected();
                    }

                    SelectShape(hit);

                    StartDragging(clickPos);
                }

                else if (!shift)
                {
                    ClearSelected();
                }
            }
        }

        if (auto mouseRelease = ev.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseRelease->button == sf::Mouse::Button::Left)
            {
                StopDragging();
            }
        }
    }
}

bool Canvas::Render()
{
    m_window.clear(canvas::BACKGROUND_COLOR);

    for (auto &shape : m_shapes)
    {
        m_window.draw(*shape->GetShape());
    }

    for (auto &shape : m_selected)
    {
        sf::FloatRect bounds = shape->GetShape()->getGlobalBounds();
        const sf::RectangleShape frame = RenderFrame(bounds);
        m_window.draw(frame);
    }

    m_panel.DrawPanel();
    m_window.display();

    return true;
}

sf::RectangleShape Canvas::RenderFrame(const sf::FloatRect &bounds) const
{
    sf::RectangleShape frame(bounds.size);

    frame.setPosition(bounds.position);
    frame.setFillColor(canvas::TRANSPARENT_COLOR);
    frame.setOutlineThickness(canvas::SELECTION_FRAME_THICKNESS);
    frame.setOutlineColor(canvas::SELECTION_FRAME_COLOR);

    return frame;
}

std::shared_ptr<IDrawableShape> Canvas::HitTest(const sf::Vector2f &point) const
{
    if (m_shapes.empty())
    {
        return nullptr;
    }

    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
    {
        const sf::FloatRect bounds = (*it)->GetShape()->getGlobalBounds();
        if (bounds.contains(point))
        {
            return *it;
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<IDrawableShape>> Canvas::GetAllSelectedShapes() const
{
    auto shapes = GetSelected();

    std::vector<std::shared_ptr<IDrawableShape>> result;

    for (const auto &s : shapes)
    {
        CollectShapes(s, result);
    }

    return result;
}

void Canvas::CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes) const
{
    auto group = std::dynamic_pointer_cast<CompositeShape>(shape);

    if (group)
    {
        for (const auto &s : group->GetShapes())
        {
            CollectShapes(s, outShapes);
        }
    }

    else
    {
        outShapes.push_back(shape);
    }
}

void Canvas::ExecuteCommand(std::unique_ptr<ICommand> cmd)
{
    cmd->Execute();
    cmds.push_back(std::move(cmd));
}

void Canvas::SetTool(std::unique_ptr<IToolState> tool)
{
    m_tool = std::move(tool);
}

std::shared_ptr<CompositeShape> Canvas::GroupShapes(const std::vector<std::shared_ptr<IDrawableShape>> &shapes)
{
    auto group = std::make_shared<CompositeShape>();

    for (const auto &s : shapes)
    {
        group->Add(s);
        s->SetInGroup(true);
    }

    m_shapes.push_back(group);
    m_selected.clear();
    m_selected.push_back(group);

    return group;
}

void Canvas::ClearTool()
{
    m_tool = nullptr;
}

void Canvas::SelectShape(const std::shared_ptr<IDrawableShape> &shape)
{
    if (std::find(m_selected.begin(), m_selected.end(), shape) == m_selected.end())
    {
        m_selected.push_back(shape);
    }
}

std::vector<std::shared_ptr<IDrawableShape>> Canvas::GetSelected() const
{
    return m_selected;
}

void Canvas::ClearSelected()
{
    m_selected.clear();
}

void Canvas::StartDragging(const sf::Vector2f &pos)
{
    m_dragging = true;
    m_lastMousePos = pos;
}

void Canvas::StopDragging()
{
    m_dragging = false;
}

bool Canvas::IsDragging() const
{
    return m_dragging;
}

void Canvas::SetLastMousePos(const sf::Vector2f &pos)
{
    m_lastMousePos = pos;
}

sf::Vector2f Canvas::GetLastMousePos() const
{
    return m_lastMousePos;
}

void Canvas::ClearCanvas()
{
    m_selected.clear();
    m_shapes.clear();
}

std::vector<std::shared_ptr<IDrawableShape>> Canvas::GetShapes() const
{
    return m_shapes;
}

void Canvas::GroupSelected()
{
    auto group = std::make_shared<CompositeShape>();

    for (const auto &s : m_selected)
    {
        group->Add(s);
        s->SetInGroup(true);
    }

    m_shapes.push_back(group);
    m_selected.clear();
    m_selected.push_back(group);
}

void Canvas::UngroupSelected()
{

    std::vector<std::shared_ptr<IDrawableShape>> toAdd;

    for (auto &s : m_selected)
    {
        auto g = std::dynamic_pointer_cast<CompositeShape>(s);

        if (g)
        {
            for (auto &child : g->GetShapes())
            {
                toAdd.push_back(child);
                child->SetInGroup(false);
            }

            m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), s), m_shapes.end());
        }
    }

    m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());
    m_selected = toAdd;
};

void Canvas::UngroupShapes(const std::vector<std::shared_ptr<IDrawableShape>> &shapes)
{
    std::vector<std::shared_ptr<IDrawableShape>> toAdd;

    for (auto &s : shapes)
    {
        auto g = std::dynamic_pointer_cast<CompositeShape>(s);

        if (g)
        {
            for (auto &child : g->GetShapes())
            {
                toAdd.push_back(child);
                child->SetInGroup(false);
            }

            m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), s), m_shapes.end());
        }
    }

    m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());
    m_selected = toAdd;
}

std::optional<sf::Event> Canvas::GetEvent() const
{
    return m_event;
}

void Canvas::SetEvent(const sf::Event &event)
{
    m_event = event;
}

void Canvas::SaveToFile(const std::string &filename, IShapeStrategy &serializer)
{
    serializer.Save(m_shapes, filename);
}