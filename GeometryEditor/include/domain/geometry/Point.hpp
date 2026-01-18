#pragma once

#include <cmath>

class Point
{
public:
    Point(float x = 0.0, float y = 0.0);

    float GetX() const;
    float GetY() const;

    float Distance(const Point &other) const;

private:
    float m_x, m_y;
};