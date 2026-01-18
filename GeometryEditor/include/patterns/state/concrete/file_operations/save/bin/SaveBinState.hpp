#pragma once

#include "../../../../../../core/canvas/Canvas.hpp"
#include "../../../../../../patterns/state/base/IToolState.hpp"
#include "../../../../../../patterns/strategy/concrete/bin/BinaryShapeStrategy.hpp"

class SaveBinState : public IToolState
{
public:
    void HandleEvent(Canvas *canvas) override;
};