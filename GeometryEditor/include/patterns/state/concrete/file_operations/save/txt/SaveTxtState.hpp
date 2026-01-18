#pragma once

#include "../../../../../../core/canvas/Canvas.hpp"
#include "../../../../../../patterns/state/base/IToolState.hpp"
#include "../../../../../../patterns/strategy/concrete/txt/TxtShapeStrategy.hpp"

class SaveTxtState : public IToolState
{
public:
    void HandleEvent(Canvas *canvas) override;
};