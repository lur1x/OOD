#pragma once

#include "IShapeVisitor.hpp"

class ColorChangeVisitor : public IShapeVisitor
{
public:
    ColorChangeVisitor(const sf::Color newColor);

    void Visit(SFMLCircleAdapter &circle) override;
    void Visit(SFMLRectangleAdapter &rectangle) override;
    void Visit(SFMLTriangleAdapter &triangle) override;

private:
    sf::Color m_newColor;
};