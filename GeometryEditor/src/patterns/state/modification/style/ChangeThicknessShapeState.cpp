#include "../../../../../include/patterns/state/concrete/modification/style/ChangeThicknessShapeState.hpp"

ChangeThicknessShapeState::ChangeThicknessShapeState(const unsigned int thickness)
    : m_thickness(thickness)
{
}

void ChangeThicknessShapeState::HandleEvent(Canvas *canvas)
{
    auto shapes = canvas->GetAllSelectedShapes();

    if (shapes.empty())
    {
        return;
    }

    canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(shapes, m_thickness));
}