#pragma once

#include <memory>

#include "../include/ICommand.hpp"
#include "../include/IDrawableShape.hpp"

class ChangeColorCommandFill : public ICommand
{
public:
    ChangeColorCommandFill(const std::shared_ptr<IDrawableShape> &shape, const sf::Color &newColor)
        : m_shape(shape), m_newColor(newColor)
    {
    }

    void Execute() override;

private:
    std::shared_ptr<IDrawableShape> m_shape;
    sf::Color m_newColor;
};