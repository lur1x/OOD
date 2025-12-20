#pragma once
#include "IDrawableShape.hpp"
#include "Constants.hpp"
#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class ShapeFactory
{
public:
    static std::shared_ptr<IDrawableShape> CreateShape(
        const SHAPES_TYPE &type,
        const std::vector<float> &params);

private:
    static std::shared_ptr<IDrawableShape> CreateCircle(const Point &center, float radius);
    static std::shared_ptr<IDrawableShape> CreateRectangle(const Point &topLeft, float width, float height);
    static std::shared_ptr<IDrawableShape> CreateTriangle(const Point &p1, const Point &p2, const Point &p3);
};