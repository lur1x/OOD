#pragma once

#include <memory>
#include "IDrawableShape.hpp"
#include "ICommand.hpp"
#include "Canvas.hpp"

class LoadCommand : public ICommand
{
public:
    LoadCommand(Canvas *canvas, std::vector<std::shared_ptr<IDrawableShape>> &shapes) : m_canvas(canvas), m_shapes(shapes) {};
    void Execute() override;
    void Undo() override;

private:
    Canvas *m_canvas;
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
};