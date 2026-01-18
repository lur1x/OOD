#pragma once

#define _USE_MATH_DEFINES

#include <memory>
#include <cmath>
#include <string>

#include "../../../../geometry/Point.hpp"
#include "../../base/IDrawableShape.hpp"
#include "../../../../../core/constants/Constants.hpp"

class SFMLCircleAdapter : public IDrawableShape
{
public:
    SFMLCircleAdapter(const Point &center, float radius);

    float GetArea() const override;
    float GetPerimeter() const override;
    std::string GetName() const override;
    std::string ToString() const override;

    bool Contains(const sf::Vector2f &point) const override;
    void Move(const sf::Vector2f &delta) override;

    void Accept(IShapeVisitor &visitor) override;
    std::vector<ShapeMemento> SaveState() const override;
    void RestoreState(const std::vector<ShapeMemento> &lastState) override;

    std::shared_ptr<sf::Shape> GetShape() const override;

    size_t GetStateSize() const override;

    void SerializeToBinary(std::ostream &out) const override;
    void SerializeToText(std::ostream &out) const override;

private:
    std::shared_ptr<sf::CircleShape> m_circle;
    Point m_center;
    float m_radius;
};
