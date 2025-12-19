#pragma once
#include "IShape.hpp"
#include "Point.hpp"
#include <memory>
#include <cmath>

class SFMLTriangleAdapter : public IShape
{
public:
    SFMLTriangleAdapter(const Point &p1, const Point &p2, const Point &p3);

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string GetName() const override;
    std::string ToString() const override;
    void DrawShape(sf::RenderWindow &window) const override;

private:
    std::unique_ptr<sf::ConvexShape> m_shape;
    Point m_p1, m_p2, m_p3;
};