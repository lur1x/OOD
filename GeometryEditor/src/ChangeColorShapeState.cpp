#include "../include/ChangeColorShapeState.hpp"

void ChangeColorShapeState::HandleEvent(Canvas *canvas)
{
    const auto shapes = canvas->GetAllSelectedShapes();

    if (shapes.empty())
    {
        return;
    }
    for (const auto s : shapes)
    {
        canvas->ExecuteCommand(std::make_unique<ChangeColorCommandFill>(s, m_color));
    }
}