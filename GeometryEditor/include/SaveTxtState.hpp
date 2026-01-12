#pragma once

#include "ITool.hpp"
#include "Canvas.hpp"
#include "TxtShapeStrategy.hpp"

class SaveTxtState : public ITool
{
public:
    void HandleEvent(Canvas *canvas) override;
};