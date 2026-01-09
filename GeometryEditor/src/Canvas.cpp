#include "../include/Canvas.hpp"
#include "../include/CompositeShape.hpp"
#include "../include/ChangeColorShapeState.hpp"
#include "../include/AddShapeState.hpp"
#include "../include/ChangeThicknessShapeState.hpp"
#include "../include/DragState.hpp"
#include <algorithm>

Canvas::Canvas(unsigned int width, unsigned int height, const std::string &title)
    : m_window(sf::VideoMode({width, height}), title)
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
        ChangeMode(event.value());
        AddNewShape(event.value());

        switch (m_mode)
        {
        case MODE::SHAPE_CHANGE:
            ChangeShape(event.value());
            break;

        case MODE::DND:
            if (!dynamic_cast<DragState *>(m_tool.get()))
            {
                SetTool(std::make_unique<DragState>());
            }
            break;
        }

        if (m_tool)
        {
            m_tool->HandleEvent(this, event.value());
        }
    }

    return true;
}

void Canvas::ChangeMode(const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    {
        const int current = static_cast<int>(m_mode);
        const int next = (current + 1) % MODE_SIZE;

        m_mode = static_cast<MODE>(next);

        switch (m_mode)
        {
        case MODE::SHAPE_CHANGE:
            ClearSelected();
            ClearTool();
            break;
        case MODE::DND:
            SetTool(std::make_unique<DragState>());
            break;
        }
    }
}

void Canvas::GroupSelectedShapes()
{
    if (m_selected.empty())
    {
        return;
    }

    auto group = std::make_shared<CompositeShape>();
    for (auto &s : m_selected)
    {
        group->Add(s);
    }

    m_shapes.push_back(group);
    m_selected.clear();
    m_selected.push_back(group);
}

void Canvas::UngroupSelectedShapes()
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
            auto it = std::find(m_shapes.begin(), m_shapes.end(), s);
            if (it != m_shapes.end())
            {
                m_shapes.erase(it);
            }
        }
    }

    m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());

    m_selected = toAdd;
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

std::shared_ptr<IDrawableShape> Canvas::GetShapeByHit(const sf::Vector2f &point) const
{
    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
    {
        auto shape = *it;

        auto group = std::dynamic_pointer_cast<CompositeShape>(shape);
        if (group)
        {
            for (auto rit = group->GetShapes().rbegin(); rit != group->GetShapes().rend(); ++rit)
            {
                if ((*rit)->GetShape()->getGlobalBounds().contains(point))
                {
                    return *rit;
                }
            }
            if (shape->Contains(point))
            {
                return shape;
            }
        }
        else if (shape->Contains(point))
        {
            return shape;
        }
    }

    return nullptr;
}

void Canvas::AddNewShape(const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>() &&
        (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Num1 ||
         event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Num2 ||
         event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Num3))

    {
        SetTool(std::make_unique<AddShapeState>());

        if (m_tool)
        {
            m_tool->HandleEvent(this, event);
        }
    }
}

void Canvas::ChangeShape(const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>() &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->scancode == sf::Keyboard::Scancode::C || keyEvent->scancode == sf::Keyboard::Scancode::X)
        {
            SetTool(std::make_unique<ChangeColorShapeState>());
        }

        if (keyEvent->scancode == sf::Keyboard::Scancode::Up || keyEvent->scancode == sf::Keyboard::Scancode::Down)
        {
            SetTool(std::make_unique<ChangeThicknessShapeState>());
        }
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

        m_selected.push_back(shape);
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
};