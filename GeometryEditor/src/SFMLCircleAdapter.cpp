#include "../include/SFMLCircleAdapter.hpp"
#include <iostream>

SFMLCircleAdapter::SFMLCircleAdapter(const Point &center, float radius)
    : m_center(center), m_radius(radius)
{

    m_shape = std::make_unique<sf::CircleShape>(radius);
    m_shape->setPosition(
        {m_center.GetX() - m_radius,
         m_center.GetY() - m_radius});

    m_shape->setFillColor(sf::Color::Green);
    m_shape->setOutlineColor(sf::Color::Black);
    m_shape->setOutlineThickness(2.0f);
}

float SFMLCircleAdapter::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

float SFMLCircleAdapter::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string SFMLCircleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << ": P=" << std::fixed << std::setprecision(2) << GetPerimeter()
        << "; S=" << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

std::string SFMLCircleAdapter::GetName() const
{
    return "CIRCLE";
}

void SFMLCircleAdapter::DrawShape(sf::RenderWindow &window) const
{
    window.draw(*m_shape);
}
