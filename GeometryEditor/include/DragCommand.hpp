#pragma once

#include "ICommand.hpp"
#include "Canvas.hpp"
#include "IDrawableShape.hpp"

class DragCommand : public ICommand
{
public:
    DragCommand(std::shared_ptr<IDrawableShape> shape, const sf::Vector2f &delta)

        : m_shape(shape), m_delta(delta)
    {
    }

    void Execute() override;

private:
    sf::Vector2f m_delta;
    std::shared_ptr<IDrawableShape> m_shape;
};