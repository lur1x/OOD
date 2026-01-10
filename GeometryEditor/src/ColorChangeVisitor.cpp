#include "../include/ColorChangeVisitor.hpp"
#include "../include/SFMLCircleAdapter.hpp"
#include "../include/SFMLTriangleAdapter.hpp"
#include "../include/SFMLRectangleAdapter.hpp"

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