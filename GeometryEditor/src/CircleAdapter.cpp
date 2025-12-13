#include "../include/CircleAdapter.hpp"
#include <iostream>

CircleAdapter::CircleAdapter(const Point &center, float radius)
    : m_circle(center, radius)
{

    m_sfmlShape = std::make_shared<sf::CircleShape>(m_circle.GetRadius());

    m_sfmlShape->setPosition(
        {static_cast<float>(m_circle.GetCenter().GetX() - m_circle.GetRadius()),
         m_circle.GetCenter().GetY() - m_circle.GetRadius()});

    applyStyle();
}

float CircleAdapter::GetArea() const
{
    return m_circle.GetArea();
}

float CircleAdapter::GetPerimeter() const
{
    return m_circle.GetPerimeter();
}

std::string CircleAdapter::ToString() const
{
    return m_circle.ToString();
}

std::shared_ptr<sf::Shape> CircleAdapter::GetShape() const
{
    if (!m_sfmlShape)
    {
        std::cerr << "WARNING: GetShape() returns null!" << std::endl;
    }
    return m_sfmlShape;
}

void CircleAdapter::applyStyle()
{
    if (!m_sfmlShape)
    {
        std::cerr << "ERROR: m_sfmlShape is null!" << std::endl;
        return;
    }

    // Яркие цвета, чтобы было видно
    m_sfmlShape->setFillColor(sf::Color::Green);  // Зеленая заливка
    m_sfmlShape->setOutlineColor(sf::Color::Red); // Красная обводка
    m_sfmlShape->setOutlineThickness(3.0f);       // Толстая обводка

    std::cout << "Style applied to circle" << std::endl;
}