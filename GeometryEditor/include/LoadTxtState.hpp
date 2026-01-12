#pragma once

#include "ITool.hpp"
#include "Canvas.hpp"
#include "ShapeBuilder.hpp"
#include "TxtShapeLoader.hpp"
#include "LoadCommand.hpp"

class LoadTxtState : public ITool
{
public:
    void HandleEvent(Canvas *canvas) override;
};