#pragma once

#include "ITool.hpp"
#include "Canvas.hpp"
#include "ChangeThicknessCommand.hpp"

class ChangeThicknessShapeState : public ITool
{
public:
    ChangeThicknessShapeState(const unsigned int thickness) : m_thickness(thickness) {}

    void HandleEvent(Canvas *canvas) override;

private:
    unsigned int m_thickness;
};