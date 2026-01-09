#pragma once

#include "ITool.hpp"
#include "DragCommand.hpp"

class DragState : public ITool
{
public:
    void HandleEvent(Canvas *canvas, const sf::Event &event) override;
};