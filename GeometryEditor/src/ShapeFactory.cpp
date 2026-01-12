#include "../include/ShapeFactory.hpp"

std::shared_ptr<IDrawableShape> ShapeFactory::CreateShape(
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

std::shared_ptr<IDrawableShape> ShapeFactory::CreateCircle(const Point &center, float radius)
{
    return std::make_shared<SFMLCircleAdapter>(center, radius);
}

std::shared_ptr<IDrawableShape> ShapeFactory::CreateRectangle(const Point &topLeft, float width, float height)
{
    return std::make_shared<SFMLRectangleAdapter>(topLeft, width, height);
}

std::shared_ptr<IDrawableShape> ShapeFactory::CreateTriangle(const Point &p1, const Point &p2, const Point &p3)
{
    return std::make_shared<SFMLTriangleAdapter>(p1, p2, p3);
}
