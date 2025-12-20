#pragma once
#include "Point.hpp"
#include "IDrawableShape.hpp"
#include "Constants.hpp"
#include <memory>
#include <cmath>

class SFMLRectangleAdapter : public IDrawableShape
{
public:
    SFMLRectangleAdapter(const Point &topLeft, float width, float height);

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string GetName() const override;
    std::string ToString() const override;
    std::shared_ptr<sf::Shape> GetShape() const override;

private:
    std::shared_ptr<sf::RectangleShape> m_shape;
    Point m_topLeft;
    float m_width;
    float m_height;
};