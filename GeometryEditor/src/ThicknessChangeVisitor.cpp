#include "../include/ThicknessChangeVisitor.hpp"
#include "../include/SFMLCircleAdapter.hpp"
#include "../include/SFMLTriangleAdapter.hpp"
#include "../include/SFMLRectangleAdapter.hpp"

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