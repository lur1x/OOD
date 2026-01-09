#include "../include/ChangeColorCommand.hpp"

void ChangeColorCommand::Execute()
{
    m_shape->GetShape()->setOutlineColor(m_newColor);
}