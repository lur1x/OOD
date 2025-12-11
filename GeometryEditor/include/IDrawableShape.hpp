#pragma once
#include "IShape.hpp"
#include <SFML/Graphics.hpp>

class IDrawableShape : public IShape
{
public:
    virtual ~IDrawableShape() = default;
    virtual std::shared_ptr<sf::Shape> GetShape() const = 0;
};