#pragma once

#include "ITool.hpp"
#include "ChangeColorCommand.hpp"
#include "Canvas.hpp"

class ChangeColorThickness : public ITool
{
public:
    ChangeColorThickness(const sf::Color &color);

    void HandleEvent(Canvas *canvas) override;

private:
    sf::Color m_color;
};