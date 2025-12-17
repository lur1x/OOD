#include "../include/SFMLCircleAdapter.hpp"
#include <iostream>

SFMLCircleAdapter::SFMLCircleAdapter(const Point &center, float radius)
    : m_center(center), m_radius(radius)
{

    m_sfmlShape = std::make_unique<sf::CircleShape>(radius);
    UpdateShapePosition();

    m_sfmlShape->setFillColor(sf::Color::Green);
    m_sfmlShape->setOutlineColor(sf::Color::Black);
    m_sfmlShape->setOutlineThickness(2.0f);
}

float SFMLCircleAdapter::GetArea() const
{
    return M_PI * GetRadius() * GetRadius();
}

float SFMLCircleAdapter::GetPerimeter() const
{
    return 2 * M_PI * GetRadius();
}

std::string SFMLCircleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << ": P=" << std::fixed << std::setprecision(2) << GetPerimeter()
        << "; S=" << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

Point SFMLCircleAdapter::GetCenter() const
{
    return m_center;
}

float SFMLCircleAdapter::GetRadius() const
{
    return m_radius;
}

void SFMLCircleAdapter::SetCenter(const Point &center)
{
    m_center = center;
    UpdateShapePosition();
}

void SFMLCircleAdapter::SetRadius(float radius)
{
    m_radius = radius;
    if (m_sfmlShape)
    {
        m_sfmlShape->setRadius(radius);
        UpdateShapePosition();
    }
}

std::string SFMLCircleAdapter::GetName() const
{
    return "CIRCLE";
}

void SFMLCircleAdapter::Draw(sf::RenderWindow &window) const
{
    if (m_sfmlShape)
    {
        window.draw(*m_sfmlShape);
    }
}

void SFMLCircleAdapter::UpdateShapePosition()
{
    if (m_sfmlShape)
    {

        m_sfmlShape->setPosition(
            {m_center.GetX() - m_radius,
             m_center.GetY() - m_radius});
    }
}
