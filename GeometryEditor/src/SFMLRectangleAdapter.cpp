#include "../include/SFMLRectangleAdapter.hpp"
#include <sstream>
#include <iomanip>

SFMLRectangleAdapter::SFMLRectangleAdapter(const Point &topLeft, float width, float height)
    : m_topLeft(topLeft), m_width(width), m_height(height)
{

    m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    m_shape->setPosition({topLeft.GetX(), topLeft.GetY()});
    m_shape->setFillColor(sf::Color::Blue);
    m_shape->setOutlineColor(sf::Color::Black);
    m_shape->setOutlineThickness(2.0f);
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
    return output::RECT;
}

std::string SFMLRectangleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

void SFMLRectangleAdapter::DrawShape(sf::RenderWindow &window) const
{
    window.draw(*m_shape);
}
