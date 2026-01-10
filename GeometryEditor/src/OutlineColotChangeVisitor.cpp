#include "../include/OutlineColorChangeVisitor.hpp"
#include "../include/SFMLCircleAdapter.hpp"
#include "../include/SFMLTriangleAdapter.hpp"
#include "../include/SFMLRectangleAdapter.hpp"

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