#include "../include/ChangeColorCommandFill.hpp"

void ChangeColorCommandFill::Execute()

{

    m_shape->GetShape()->setFillColor(m_newColor);
}