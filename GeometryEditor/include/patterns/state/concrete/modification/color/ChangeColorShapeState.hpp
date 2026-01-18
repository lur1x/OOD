#pragma once

#include <memory>

#include "../../../base/IToolState.hpp"
#include "../../../../../core/constants/Constants.hpp"
#include "../../../../../core/canvas/Canvas.hpp"
#include "../../../../command/concrete/modification/color/ChangeColorCommandFill.hpp"

class ChangeColorShapeState : public IToolState
{
public:
    ChangeColorShapeState(const sf::Color &color);

    void HandleEvent(Canvas *canvas) override;

private:
    sf::Color m_color;
};