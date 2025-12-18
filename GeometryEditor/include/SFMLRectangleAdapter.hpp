#pragma once
#include "IShape.hpp"
#include "Point.hpp"
#include <memory>
#include <cmath>

class SFMLRectangleAdapter : public IShape
{
private:
    std::unique_ptr<sf::RectangleShape> m_shape;
    Point m_topLeft;
    float m_width;
    float m_height;

public:
    SFMLRectangleAdapter(const Point &topLeft, float width, float height);

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string GetName() const override;
    std::string ToString() const override;
    void DrawShape(sf::RenderWindow &window) const override;
};