#include "../include/ChangeThicknessShapeState.hpp"

void ChangeThicknessShapeState::HandleEvent(Canvas *canvas)
{
    auto shapes = canvas->GetAllSelectedShapes();
    if (shapes.empty())
    {
        return;
    }
    for (const auto s : shapes)
    {
        canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(s, m_thickness));
    }
}