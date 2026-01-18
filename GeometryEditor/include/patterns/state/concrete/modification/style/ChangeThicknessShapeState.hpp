#pragma once

#include "../../../base/IToolState.hpp"
#include "../../../../../core/constants/Constants.hpp"
#include "../../../../../core/canvas/Canvas.hpp"
#include "../../../../command/concrete/modification/style/ChangeThicknessCommand.hpp"

class ChangeThicknessShapeState : public IToolState
{
public:
    ChangeThicknessShapeState(const unsigned int thickness);

    void HandleEvent(Canvas *canvas) override;

private:
    unsigned int m_thickness;
};