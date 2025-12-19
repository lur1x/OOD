#pragma once
#include "IShape.hpp"
#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"
#include "Constants.hpp"
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class ShapeFactory
{
public:
    static std::unique_ptr<IShape> CreateShape(
        const SHAPES_TYPE &type,
        const std::vector<float> &params);

private:
    static std::unique_ptr<IShape> CreateCircle(const Point &center, float radius);
    static std::unique_ptr<IShape> CreateRectangle(const Point &topLeft, float width, float height);
    static std::unique_ptr<IShape> CreateTriangle(const Point &p1, const Point &p2, const Point &p3);
};