#pragma once

#include "../../../../base/IToolState.hpp"
#include "../../../../../builder/concrete/ShapeBuilder.hpp"
#include "../../../../../../core/canvas/Canvas.hpp"
#include "../../../../../../infrastructure/persistence/loader/concrete/txt/TxtShapeLoader.hpp"
#include "../../../../../command/concrete/file_operations/LoadCommand.hpp"

class LoadTxtState : public IToolState
{
public:
    void HandleEvent(Canvas *canvas) override;
};