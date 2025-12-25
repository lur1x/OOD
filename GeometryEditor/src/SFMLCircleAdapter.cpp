#include "../include/SFMLCircleAdapter.hpp"

SFMLCircleAdapter::SFMLCircleAdapter(const Point &center, float radius)
    : m_center(center), m_radius(radius)
{

    m_circle = std::make_shared<sf::CircleShape>(radius);
    m_circle->setPosition(
        {m_center.GetX() - m_radius,
         m_center.GetY() - m_radius});

    m_circle->setFillColor(sf::Color::Green);
    m_circle->setOutlineColor(sf::Color::Black);
    m_circle->setOutlineThickness(2.0f);
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
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

std::string SFMLCircleAdapter::GetName() const
{
    return output::CIRCLE;
}

std::shared_ptr<sf::Shape> SFMLCircleAdapter::GetShape() const
{
    return m_circle;
}

bool SFMLCircleAdapter::Contains(const sf::Vector2f &point) const
{
    return GetShape()->getGlobalBounds().contains(point);
}

void SFMLCircleAdapter::Move(const sf::Vector2f &delta)
{
    m_center = Point(m_center.GetX() + delta.x, m_center.GetY() + delta.y);

    m_circle->move(delta);
}