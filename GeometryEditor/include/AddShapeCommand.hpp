#pragma once

#include <memory>
#include "ICommand.hpp"
#include "Canvas.hpp"

class AddShapeCommand : public ICommand
{
public:
    AddShapeCommand(Canvas *canvas, std::shared_ptr<IDrawableShape> shape);

    void Execute() override;
    void Undo() override;

private:
    Canvas *m_canvas;
    std::shared_ptr<IDrawableShape> m_shape;
};