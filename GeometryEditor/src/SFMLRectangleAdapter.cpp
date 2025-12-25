#include "../include/SFMLRectangleAdapter.hpp"

SFMLRectangleAdapter::SFMLRectangleAdapter(const Point &topLeft, float width, float height)
    : m_topLeft(topLeft), m_width(width), m_height(height)
{

    m_rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
    m_rectangle->setPosition({topLeft.GetX(), topLeft.GetY()});
    m_rectangle->setFillColor(sf::Color::Blue);
    m_rectangle->setOutlineColor(sf::Color::Black);
    m_rectangle->setOutlineThickness(2.0f);
}

float SFMLRectangleAdapter::GetArea() const
{
    return m_width * m_height;
}

float SFMLRectangleAdapter::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string SFMLRectangleAdapter::GetName() const
{
    return output::RECTANGLE;
}

std::string SFMLRectangleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

std::shared_ptr<sf::Shape> SFMLRectangleAdapter::GetShape() const
{
    return m_rectangle;
}

bool SFMLRectangleAdapter::Contains(const sf::Vector2f &point) const
{
    m_rectangle->setPosition({m_topLeft.GetX(), m_topLeft.GetY()});

    sf::FloatRect bounds = m_rectangle->getGlobalBounds();
    return bounds.contains(point);
}

void SFMLRectangleAdapter::Move(const sf::Vector2f &delta)
{
    m_topLeft = Point(m_topLeft.GetX() + delta.x, m_topLeft.GetY() + delta.y);

    m_rectangle->move(delta);
}