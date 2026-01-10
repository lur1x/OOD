#pragma once

#include <memory>
#include <cmath>

#include "Point.hpp"
#include "IDrawableShape.hpp"
#include "Constants.hpp"

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

    void Accept(IShapeVisitor &visitor) override;
    std::vector<ShapeMemento> SaveState() const override;
    void RestoreState(const std::vector<ShapeMemento> &lastState) override;
    size_t GetStateSize() const override;

    std::shared_ptr<sf::Shape> GetShape() const override;

private:
    std::shared_ptr<sf::RectangleShape> m_rectangle;
    Point m_topLeft;
    float m_width;
    float m_height;
};