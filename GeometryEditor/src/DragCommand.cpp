#include "../include/DragCommand.hpp"

void DragCommand::Execute()
{
    m_shape->Move(m_delta);
}