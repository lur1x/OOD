#pragma once

#include <memory>

#include "ICommand.hpp"
#include "IDrawableShape.hpp"
#include "Constants.hpp"

class ChangeColorCommand : public ICommand
{
public:
    ChangeColorCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const sf::Color &newColor);

    void Execute() override;
    void Undo() override;

private:
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
    sf::Color m_newColor;
    std::vector<std::vector<ShapeMemento>> m_before;
};