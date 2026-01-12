#pragma once

#include "Canvas.hpp"
#include "ITool.hpp"
#include "ShapeBuilder.hpp"
#include "BinaryShapeLoader.hpp"
#include "LoadCommand.hpp"

class LoadBinState : public ITool
{
public:
    void HandleEvent(Canvas *canvas) override;
};