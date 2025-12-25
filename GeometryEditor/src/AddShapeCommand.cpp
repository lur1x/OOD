#include "../include/AddShapeCommand.hpp"

void AddShapeCommand::Execute()
{
    m_canvas->AddShape(m_shape);
}