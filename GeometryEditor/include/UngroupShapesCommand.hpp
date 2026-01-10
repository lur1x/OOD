#pragma once

#include <vector>
#include <memory>

#include "ICommand.hpp"
#include "IDrawableShape.hpp"
#include "Canvas.hpp"

class UngroupShapesCommand : public ICommand
{
public:
    UngroupShapesCommand(Canvas *canvas);

    void Execute() override;
    void Undo() override;

private:
    std::vector<std::shared_ptr<IDrawableShape>> m_before;
    Canvas *m_canvas;
};