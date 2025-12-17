#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class IShape
{
public:
    virtual ~IShape() = default;

    virtual float GetArea() const = 0;
    virtual float GetPerimeter() const = 0;
    virtual std::string GetName() const = 0;
    virtual std::string ToString() const = 0;

    virtual void Draw(sf::RenderWindow &window) const = 0;

    // virtual void draw(ICanvas &canvas) const = 0; //  на подумать

protected:
    std::string m_name;
};
