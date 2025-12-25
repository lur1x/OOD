#include "../include/ChangeThicknessCommand.hpp"

void ChangeThicknessCommand::Execute()
{
    m_shape->GetShape()->setOutlineThickness(m_newThickness);
}