#pragma once

#include <SFML/Graphics.hpp>
#include "IShape.hpp"

class IDrawableShape : public IShape
{
public:
    virtual ~IDrawableShape() = default;
    virtual std::shared_ptr<sf::Shape> GetShape() const = 0;
};
