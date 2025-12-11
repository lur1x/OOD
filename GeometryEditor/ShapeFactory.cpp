#include "ShapeFactory.hpp"
#include "Point.hpp"

std::unique_ptr<IDrawableShape> ShapeFactory::CreateShape(
    const std::string &type,
    const std::vector<float> &params)
{
    if (type == "CIRCLE" && params.size() == 3)
    {
        Point center(params[0], params[1]);
        return std::make_unique<CircleAdapter>(center, params[2]);
    }
    return nullptr;
}
