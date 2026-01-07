#include "../include/Canvas.hpp"
#include "../include/CompositeShape.hpp"
#include "../include/ChangeColorShapeState.hpp"
#include "../include/AddShapeState.hpp"
#include "../include/ChangeThicknessShapeState.hpp"
#include "../include/DragState.hpp"
#include <algorithm>

bool Canvas::IsOpen() const
{
    return m_window.isOpen();
}

void Canvas::Draw()
{
    while (IsOpen())
    {
        if (!HandleEvents())
            break;
        if (!Render())
            break;
    }
}

void Canvas::AddShape(std::shared_ptr<IDrawableShape> shape)
{
    m_shapes.push_back(std::move(shape));
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
        SelectEvent(*event);

        m_panel.HandleMouseEvent(*event);

        if (m_tool)
        {
            m_tool->HandleEvent(this);
            if (!m_panel.IsDragMode())
            {
                SetTool(nullptr);
            }
        }
    }
    return true;
}

void Canvas::SelectEvent(const sf::Event &event)
{
    if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
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

bool Canvas::Render()
{
    m_window.clear(canvas::BACKGROUND_COLOR);

    for (auto &shape : m_shapes)
    {
        m_window.draw(*shape->GetShape());
    }

    for (auto &shape : m_selected)
    {

        const sf::FloatRect bounds = shape->GetShape()->getGlobalBounds();
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

std::shared_ptr<IDrawableShape> Canvas::HitTest(const sf::Vector2f &point)
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

std::vector<std::shared_ptr<IDrawableShape>> Canvas::GetAllSelectedShapes()
{
    auto shapes = GetSelected();

    std::vector<std::shared_ptr<IDrawableShape>> result;

    for (const auto &s : shapes)
    {
        CollectShapes(s, result);
    }
    return result;
}

void Canvas::CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes)
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
}

void Canvas::SetTool(std::unique_ptr<ITool> tool)
{
    m_tool = std::move(tool);
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

void Canvas::GroupSelected()
{
    auto group = std::make_shared<CompositeShape>();

    for (const auto &s : m_selected)
    {
        group->Add(s);
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
            }
            m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), s), m_shapes.end());
        }
    }

    m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());

    m_selected = toAdd;
}

void Canvas::SetEvent(const sf::Event &event)
{
}

std::optional<sf::Event> Canvas::GetEvent() const
{
}
std::unique_ptr<ITool> Canvas::GetTool()
{
}