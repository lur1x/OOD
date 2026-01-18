#include "../../../../../include/patterns/state/concrete/modification/color/ChangeColorThicknessState.hpp"

ChangeColorThicknessState::ChangeColorThicknessState(const sf::Color &color)
    : m_color(color)
{
}

void ChangeColorThicknessState::HandleEvent(Canvas *canvas)
{
    const auto shapes = canvas->GetAllSelectedShapes();

    if (shapes.empty())
    {
        return;
    }

    canvas->ExecuteCommand(std::make_unique<ChangeColorCommand>(shapes, m_color));
}