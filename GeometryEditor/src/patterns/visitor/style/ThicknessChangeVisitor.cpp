#include "../../../../include/patterns/visitor/concrete/style/ThicknessChangeVisitor.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/circle/SFMLCircleAdapter.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/triangle/SFMLTriangleAdapter.hpp"
#include "../../../../include/domain/shapes/adapter/primitive/rectangle/SFMLRectangleAdapter.hpp"

ThicknessChangeVisitor::ThicknessChangeVisitor(const unsigned int newThickness)
    : m_newThickness(newThickness)
{
}

void ThicknessChangeVisitor::Visit(SFMLCircleAdapter &circle)
{
    circle.GetShape()->setOutlineThickness(m_newThickness);
}

void ThicknessChangeVisitor::Visit(SFMLRectangleAdapter &rectangle)
{
    rectangle.GetShape()->setOutlineThickness(m_newThickness);
}

void ThicknessChangeVisitor::Visit(SFMLTriangleAdapter &triangle)
{
    triangle.GetShape()->setOutlineThickness(m_newThickness);
}