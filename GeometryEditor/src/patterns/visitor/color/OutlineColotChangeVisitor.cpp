#include "../../../../include/patterns/visitor/concrete/color/OutlineColorChangeVisitor.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/circle/SFMLCircleAdapter.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/triangle/SFMLTriangleAdapter.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/rectangle/SFMLRectangleAdapter.hpp"

OutlineColorChangeVisitor::OutlineColorChangeVisitor(const sf::Color newColor)
    : m_newColor(newColor)
{
}

void OutlineColorChangeVisitor::Visit(SFMLCircleAdapter &circle)
{
    circle.GetShape()->setOutlineColor(m_newColor);
}

void OutlineColorChangeVisitor::Visit(SFMLRectangleAdapter &rectangle)
{
    rectangle.GetShape()->setOutlineColor(m_newColor);
}

void OutlineColorChangeVisitor::Visit(SFMLTriangleAdapter &triangle)
{
    triangle.GetShape()->setOutlineColor(m_newColor);
}