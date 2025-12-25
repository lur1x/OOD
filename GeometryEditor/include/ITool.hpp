#pragma once
#include <SFML/Graphics.hpp>

class Canvas;

class ITool
{
public:
    virtual ~ITool() = default;
    virtual void HandleEvent(Canvas *canvas, const sf::Event &event) = 0;
};