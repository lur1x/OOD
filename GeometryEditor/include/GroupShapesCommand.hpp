#pragma once

#include <vector>
#include <memory>

#include "ICommand.hpp"
#include "IDrawableShape.hpp"
#include "Canvas.hpp"

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