#include "../include/Canvas.hpp"
#include <iostream>

Canvas::Canvas(unsigned int width, unsigned int height, const std::string &title)
    : m_window(sf::VideoMode({width, height}), title)
{
    m_window.setFramerateLimit(60);
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
    }
    return true;
}

bool Canvas::Render()
{
    m_window.clear(sf::Color::White);

    for (const auto &shape : m_shapes)
    {
        m_window.draw(*shape->GetShape());
    }

    m_window.display();
    return true;
}
