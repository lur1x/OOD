#include "../include/ShapeFactory.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

std::unique_ptr<IShape> ShapeFactory::CreateShape(
    const SHAPES_TYPE &type,
    const std::vector<float> &params)
{

    switch (type)
    {
    case SHAPES_TYPE::RECTANGLE_T:
        return CreateRectangle(Point(params[0], params[1]), params[2], params[3]);
    case SHAPES_TYPE::TRIANGLE_T:
        return CreateTriangle(
            Point(params[0], params[1]),
            Point(params[2], params[3]),
            Point(params[4], params[5]));
    case SHAPES_TYPE::CIRCLE_T:
        return CreateCircle(Point(params[0], params[1]), params[2]);
    default:
        return nullptr;
    }
}

std::unique_ptr<IShape> ShapeFactory::CreateCircle(const Point &center, float radius)
{
    return std::make_unique<SFMLCircleAdapter>(center, radius);
}

std::unique_ptr<IShape> ShapeFactory::CreateRectangle(const Point &topLeft, float width, float height)
{
    return std::make_unique<SFMLRectangleAdapter>(topLeft, width, height);
}

std::unique_ptr<IShape> ShapeFactory::CreateTriangle(const Point &p1, const Point &p2, const Point &p3)
{
    return std::make_unique<SFMLTriangleAdapter>(p1, p2, p3);
}
