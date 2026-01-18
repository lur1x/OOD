#pragma once

#include <SFML/Graphics.hpp>

class Canvas;

class IToolState
{
public:
    virtual ~IToolState() = default;
    virtual void HandleEvent(Canvas *canvas) = 0;
};