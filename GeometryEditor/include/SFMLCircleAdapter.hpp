#define _USE_MATH_DEFINES
#pragma once
#include "Point.hpp"
#include "IShape.hpp"
#include <memory>
#include <cmath>
#include <string>

class SFMLCircleAdapter : public IShape
{
public:
    SFMLCircleAdapter(const Point &center, float radius);

    float GetArea() const;
    float GetPerimeter() const;

    std::string GetName() const override;
    std::string ToString() const;

    Point GetCenter() const;
    float GetRadius() const;

    void SetCenter(const Point &center);
    void SetRadius(float radius);

    void Draw(sf::RenderWindow &window) const override;

private:
    std::unique_ptr<sf::CircleShape> m_sfmlShape;
    Point m_center;
    float m_radius;

    void UpdateShapePosition(); // на подумать
};
