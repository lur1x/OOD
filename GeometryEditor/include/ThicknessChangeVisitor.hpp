#pragma once

#include "../include/IShapeVisitor.hpp"

class ThicknessChangeVisitor : public IShapeVisitor
{
public:
    ThicknessChangeVisitor(const unsigned int newThickness);

    void Visit(SFMLCircleAdapter &circle) override;
    void Visit(SFMLRectangleAdapter &rectangle) override;
    void Visit(SFMLTriangleAdapter &triangle) override;

private:
    unsigned int m_newThickness;
};