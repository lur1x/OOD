#include "../include/Circle.hpp"

Circle::Circle(const Point &center, float radius)
    : m_center(center), m_radius(radius) {}

float Circle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

float Circle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

Point Circle::GetCenter() const
{
    return m_center;
}

float Circle::GetRadius() const
{
    return m_radius;
}

std::string Circle::ToString() const
{
    return "Circle: Center=(" + std::to_string(m_center.GetX()) + "," +
           std::to_string(m_center.GetY()) + "), Radius=" +
           std::to_string(m_radius);
}