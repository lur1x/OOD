#pragma once

#include "ITool.hpp"
#include "Canvas.hpp"
#include "BinaryShapeStrategy.hpp"

class SaveBinState : public ITool
{
public:
    void HandleEvent(Canvas *canvas) override;
};