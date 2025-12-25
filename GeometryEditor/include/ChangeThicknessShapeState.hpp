#pragma once

#include "ITool.hpp"
#include "Canvas.hpp"
#include "ChangeThicknessCommand.hpp"

class ChangeThicknessShapeState : public ITool
{
public:
    void HandleEvent(Canvas *canvas, const sf::Event &event) override;
};