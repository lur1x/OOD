#pragma once

#include <SFML/Graphics.hpp>

class IShape
{
public:
    virtual ~IShape() = default;

    virtual float GetArea() const = 0;
    virtual float GetPerimeter() const = 0;
    virtual std::string GetName() const = 0;
    virtual std::string ToString() const = 0;
};
