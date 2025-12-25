#pragma once

#include <memory>

#include "ITool.hpp"
#include "Constants.hpp"
#include "Canvas.hpp"
#include "ChangeColorCommand.hpp"

class ChangeColorShapeState : public ITool
{
public:
    void HandleEvent(Canvas *canvas, const sf::Event &event) override;

private:
    sf::Color GetNextColor(const sf::Color &colorShape) const;

    SHAPE_COLORS GetEnumFromColor(const sf::Color &color) const;
};