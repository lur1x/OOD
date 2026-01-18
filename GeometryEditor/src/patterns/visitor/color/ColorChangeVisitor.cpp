#include "../../../../include/patterns/visitor/concrete/color/ColorChangeVisitor.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/circle/SFMLCircleAdapter.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/triangle/SFMLTriangleAdapter.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/rectangle/SFMLRectangleAdapter.hpp"

ColorChangeVisitor::ColorChangeVisitor(const sf::Color newColor)
    : m_newColor(newColor)
{
}

void ColorChangeVisitor::Visit(SFMLCircleAdapter &circle)
{
    circle.GetShape()->setFillColor(m_newColor);
}

void ColorChangeVisitor::Visit(SFMLRectangleAdapter &rectangle)
{
    rectangle.GetShape()->setFillColor(m_newColor);
}

void ColorChangeVisitor::Visit(SFMLTriangleAdapter &triangle)
{
    triangle.GetShape()->setFillColor(m_newColor);
}