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

float SFMLTriangleAdapter::calculateSideLength(const Point &a, const Point &b) const
{
    float dx = a.GetX() - b.GetX();
    float dy = a.GetY() - b.GetY();
    return std::sqrt(dx * dx + dy * dy);
}

float SFMLTriangleAdapter::GetArea() const
{
    // Формула Герона
    float a = calculateSideLength(m_p1, m_p2);
    float b = calculateSideLength(m_p2, m_p3);
    float c = calculateSideLength(m_p3, m_p1);
    float p = (a + b + c) / 2.0f;

    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float SFMLTriangleAdapter::GetPerimeter() const
{
    return calculateSideLength(m_p1, m_p2) +
           calculateSideLength(m_p2, m_p3) +
           calculateSideLength(m_p3, m_p1);
}

std::string SFMLTriangleAdapter::GetName() const
{
    return "TRIANGLE";
}

std::string SFMLTriangleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << ": P=" << std::fixed << std::setprecision(2) << GetPerimeter()
        << "; S=" << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

void SFMLTriangleAdapter::DrawShape(sf::RenderWindow &window) const
{
    window.draw(*m_shape);
}