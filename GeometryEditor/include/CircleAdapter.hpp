
#pragma once
#include "IDrawableShape.hpp"
#include "Circle.hpp"
#include <SFML/Graphics.hpp>

class CircleAdapter : public IDrawableShape
{
public:
    CircleAdapter(const Point &center, float radius);

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string ToString() const override;

    std::shared_ptr<sf::Shape> GetShape() const override;

private:
    Circle m_circle;
    std::shared_ptr<sf::CircleShape> m_sfmlShape;

    void applyStyle();
};