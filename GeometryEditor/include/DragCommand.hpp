#pragma once

#include "ICommand.hpp"
#include "Canvas.hpp"
#include "IDrawableShape.hpp"

class DragCommand : public ICommand
{
public:
    DragCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes);

    void Execute() override;
    void Undo() override;

private:
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
    std::vector<std::vector<ShapeMemento>> m_before;
};