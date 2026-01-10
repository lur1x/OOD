#pragma once

#include <SFML/Graphics.hpp>

class SFMLCircleAdapter;
class SFMLRectangleAdapter;
class SFMLTriangleAdapter;

class IShapeVisitor
{
public:
    virtual void Visit(SFMLCircleAdapter &circle) = 0;
    virtual void Visit(SFMLRectangleAdapter &rectangle) = 0;
    virtual void Visit(SFMLTriangleAdapter &triangle) = 0;
};