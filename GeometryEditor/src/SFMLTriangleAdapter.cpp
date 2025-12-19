#include "../include/SFMLTriangleAdapter.hpp"
#include <sstream>
#include <iomanip>

SFMLTriangleAdapter::SFMLTriangleAdapter(const Point &p1, const Point &p2, const Point &p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{

    m_shape = std::make_unique<sf::ConvexShape>(3);
    m_shape->setPoint(0, sf::Vector2f(p1.GetX(), p1.GetY()));
    m_shape->setPoint(1, sf::Vector2f(p2.GetX(), p2.GetY()));
    m_shape->setPoint(2, sf::Vector2f(p3.GetX(), p3.GetY()));
    m_shape->setFillColor(sf::Color::Red);
    m_shape->setOutlineColor(sf::Color::Black);
    m_shape->setOutlineThickness(2.0f);
}

float SFMLTriangleAdapter::GetArea() const
{
    float a = m_p1.Distance(m_p2);
    float b = m_p2.Distance(m_p3);
    float c = m_p3.Distance(m_p1);
    float p = (a + b + c) / 2.0f;

    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float SFMLTriangleAdapter::GetPerimeter() const
{
    return m_p1.Distance(m_p2);
    +m_p2.Distance(m_p3) +
        m_p3.Distance(m_p1);
}

std::string SFMLTriangleAdapter::GetName() const
{
    return output::TRIANGLE;
}

std::string SFMLTriangleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

void SFMLTriangleAdapter::DrawShape(sf::RenderWindow &window) const
{
    window.draw(*m_shape);
}