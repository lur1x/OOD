#pragma once

#include <memory>
#include <cmath>

#include "../../../../geometry/Point.hpp"
#include "../../base/IDrawableShape.hpp"
#include "../../../../../core/constants/Constants.hpp"

class SFMLTriangleAdapter : public IDrawableShape
{
public:
    SFMLTriangleAdapter(const Point &p1, const Point &p2, const Point &p3);

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

    void SerializeToBinary(std::ostream &out) const override;
    void SerializeToText(std::ostream &out) const override;

private:
    std::shared_ptr<sf::ConvexShape> m_triangle;
    Point m_p1, m_p2, m_p3;
};