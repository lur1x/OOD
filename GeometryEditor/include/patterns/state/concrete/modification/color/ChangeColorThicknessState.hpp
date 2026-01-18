#pragma once

#include "../../../base/IToolState.hpp"
#include "../../../../../core/constants/Constants.hpp"
#include "../../../../../core/canvas/Canvas.hpp"
#include "../../../../command/concrete/modification/color/ChangeColorCommand.hpp"

class ChangeColorThicknessState : public IToolState
{
public:
    ChangeColorThicknessState(const sf::Color &color);

    void HandleEvent(Canvas *canvas) override;

private:
    sf::Color m_color;
};