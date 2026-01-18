#pragma once

#include "../../../base/ICommand.hpp"
#include "../../../../../core/canvas/Canvas.hpp"
#include "../../../../../domain/shapes/adapter/base/IDrawableShape.hpp"

class ChangeThicknessCommand : public ICommand
{
public:
    ChangeThicknessCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const float newThickness);

    void Execute() override;
    void Undo() override;

private:
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
    float m_newThickness;
    std::vector<std::vector<ShapeMemento>> m_before;
};