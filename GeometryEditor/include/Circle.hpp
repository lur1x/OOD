#pragma once
#include "Point.hpp"
#include "Constants.hpp"
#include <cmath>
#include <string>

class Circle
{
public:
    Circle(const Point &center, float radius);

    float GetArea() const;
    float GetPerimeter() const;

    Point GetCenter() const;
    float GetRadius() const;

    std::string ToString() const;

private:
    Point m_center;
    float m_radius;
};