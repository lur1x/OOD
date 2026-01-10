#include "../include/ChangeColorThickness.hpp"

ChangeColorThickness::ChangeColorThickness(const sf::Color &color)
    : m_color(color)
{
}

void ChangeColorThickness::HandleEvent(Canvas *canvas)
{
    const auto shapes = canvas->GetAllSelectedShapes();

    if (shapes.empty())
    {
        return;
    }

    canvas->ExecuteCommand(std::make_unique<ChangeColorCommand>(shapes, m_color));
}