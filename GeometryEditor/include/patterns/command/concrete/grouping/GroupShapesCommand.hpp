#pragma once

#include <vector>
#include <memory>

#include "../../base/ICommand.hpp"
#include "../../../../core/canvas/Canvas.hpp"
#include "../../../../domain/shapes/adapter/base/IDrawableShape.hpp"

class GroupShapesCommand : public ICommand
{
public:
    GroupShapesCommand(Canvas *canvas);

    void Execute() override;
    void Undo() override;

private:
    std::vector<std::shared_ptr<IDrawableShape>> m_before;
    Canvas *m_canvas;
};