#pragma once
#include "Point.hpp"
#include "IDrawableShape.hpp"
#include "Constants.hpp"
#include <memory>
#include <cmath>

class SFMLTriangleAdapter : public IDrawableShape
{
public:
    SFMLTriangleAdapter(const Point &p1, const Point &p2, const Point &p3);

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string GetName() const override;
    std::string ToString() const override;

    std::shared_ptr<sf::Shape> GetShape() const override;

private:
    std::shared_ptr<sf::ConvexShape> m_shape;
    Point m_p1, m_p2, m_p3;
};