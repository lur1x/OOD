#include "../include/ChangeColorShapeState.hpp"

ChangeColorShapeState::ChangeColorShapeState(const sf::Color &color)
    : m_color(color)
{
}

void ChangeColorShapeState::HandleEvent(Canvas *canvas)
{
    const auto shapes = canvas->GetAllSelectedShapes();

    if (shapes.empty())
    {
        return;
    }

    canvas->ExecuteCommand(std::make_unique<ChangeColorCommandFill>(shapes, m_color));
}