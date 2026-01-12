#include "../include/AddShapeState.hpp"

AddShapeState::AddShapeState(const enum SHAPES_TYPE &shape_type, const sf::Vector2f &startPos)
    : m_shape_type(shape_type), m_startPos(startPos)
{
}

Point ToPoint(const sf::Vector2f &vec)
{
    return Point(vec.x, vec.y);
}

void AddShapeState::HandleEvent(Canvas *canvas)
{

    float centerX = window::WIDTH_SIZE / 2;
    float centerY = window::HEIGHT_SIZE / 2;

    std::shared_ptr<IDrawableShape> newShape;

    switch (m_shape_type)
    {
    case SHAPES_TYPE::CIRCLE_T:
        newShape = std::make_shared<SFMLCircleAdapter>(Point(centerX, centerY), 50.0f);
        break;

    case SHAPES_TYPE::RECTANGLE_T:
        newShape = std::make_shared<SFMLRectangleAdapter>(
            Point(centerX, centerY),
            100.0f,
            100.0f);
        break;

    case SHAPES_TYPE::TRIANGLE_T:
        newShape = std::make_shared<SFMLTriangleAdapter>(
            Point(centerX, centerY),
            Point(centerX, centerY + 100),
            Point(centerX + 100, centerY + 50));
        break;

    default:
        return;
    }

    canvas->ExecuteCommand(std::make_unique<AddShapeCommand>(canvas, newShape));
}