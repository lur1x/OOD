#pragma once

#include "../../base/IShapeVisitor.hpp"

class OutlineColorChangeVisitor : public IShapeVisitor
{
public:
    OutlineColorChangeVisitor(const sf::Color newColor);

    void Visit(SFMLCircleAdapter &circle) override;
    void Visit(SFMLRectangleAdapter &rectangle) override;
    void Visit(SFMLTriangleAdapter &triangle) override;

private:
    sf::Color m_newColor;
};