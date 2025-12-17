#include "../include/Point.hpp"

Point::Point(float x, float y) : m_x(x), m_y(y) {};

float Point::GetX() const
{
    return m_x;
}

float Point::GetY() const
{
    return m_y;
}

void Point::SetX(float newX)
{
    m_x = newX;
}
void Point::SetY(float newY)
{
    m_y = newY;
}

float Point::Distance(const Point &other) const
{
    return std::sqrt((GetX() - other.GetX()) * (GetX() - other.GetX()) + (GetY() - other.GetY()) * (GetY() - other.GetY()));
}