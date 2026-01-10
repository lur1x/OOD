#pragma once

#include <memory>

#include "ITool.hpp"
#include "Constants.hpp"
#include "Canvas.hpp"
#include "ChangeColorCommandFill.hpp"

class ChangeColorShapeState : public ITool
{
public:
    ChangeColorShapeState(const sf::Color &color);

    void HandleEvent(Canvas *canvas) override;

private:
    sf::Color m_color;
};