#include "../include/Canvas.hpp"
#include "../include/CompositeShape.hpp"
#include "../include/Constants.hpp"
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

bool Canvas::HandleEvents()
{
    while (auto event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
            return false;
        }
        HandleMouseDragEvent(*event);
        HandleGroupEvent(*event);
    }

    HandleDragEvent();
    return true;
}

void Canvas::HandleMouseDragEvent(const sf::Event &event)
{
    if (event.is<sf::Event::MouseButtonPressed>() &&
        event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
    {
        auto mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        sf::Vector2f clickPos = m_window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});

        bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
        auto hit = HitTest(clickPos);

        if (hit)
        {
            if (!shift)
                m_selected.clear();

            if (std::find(m_selected.begin(), m_selected.end(), hit) == m_selected.end())
                m_selected.push_back(hit);

            m_dragging = true;
            m_lastMousePos = clickPos;
        }
        else if (!shift)
            m_selected.clear();
    }

    if (event.is<sf::Event::MouseButtonReleased>() &&
        event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
    {
        m_dragging = false;
    }
}

void Canvas::HandleGroupEvent(const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            if (keyEvent->scancode == sf::Keyboard::Scancode::G)
            {
                GroupSelectedShapes();
            }

            if (keyEvent->scancode == sf::Keyboard::Scancode::U)
            {
                UngroupSelectedShapes();
            }
        }
    }
}

void Canvas::HandleDragEvent()
{
    if (m_dragging)
    {
        auto mousePos = sf::Mouse::getPosition(m_window);
        sf::Vector2f currPos = m_window.mapPixelToCoords({mousePos.x, mousePos.y});
        sf::Vector2f delta = currPos - m_lastMousePos;

        if (delta.x != 0 || delta.y != 0)
        {
            for (auto &s : m_selected)
                s->Move(delta);

            m_lastMousePos = currPos;
        }
    }
}

void Canvas::GroupSelectedShapes()
{
    if (m_selected.empty())
        return;

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
                toAdd.push_back(child);

            auto it = std::remove(m_shapes.begin(), m_shapes.end(), s);
            m_shapes.erase(it, m_shapes.end());
        }
    }

    m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());

    m_selected = toAdd;
}

bool Canvas::Render()
{
    m_window.clear(canvas::BACKGROUND_COLOR);

    for (const auto &shape : m_shapes)
    {
        m_window.draw(*shape->GetShape());
    }

    for (auto &s : m_selected)
    {
        m_window.draw(*s->GetShape());

        sf::FloatRect bounds = s->GetShape()->getGlobalBounds();

        sf::RectangleShape frame(bounds.size);
        frame.setPosition(bounds.position);
        frame.setFillColor(canvas::TRANSPARENT_COLOR);
        frame.setOutlineThickness(canvas::SELECTION_FRAME_THICKNESS);
        frame.setOutlineColor(canvas::SELECTION_FRAME_COLOR);
        m_window.draw(frame);
    }

    m_window.display();
    return true;
}

std::shared_ptr<IDrawableShape> Canvas::HitTest(const sf::Vector2f &point)
{
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
