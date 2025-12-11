#include "Point.hpp"

Point::Point(float x, float y) : m_x(x), m_y(y) {};

float Point::GetX() const
{
    return m_x;
}

float Point::GetY() const
{
    return m_y;
}
