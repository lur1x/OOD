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

    bool Contains(const sf::Vector2f &point) const override;
    void Move(const sf::Vector2f &delta) override;

    std::shared_ptr<sf::Shape> GetShape() const override;

private:
    std::shared_ptr<sf::RectangleShape> m_rectangle;
    Point m_topLeft;
    float m_width;
    float m_height;
};