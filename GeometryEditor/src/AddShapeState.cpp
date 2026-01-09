#include "../include/AddShapeState.hpp"

Point ToPoint(const sf::Vector2f &vec)
{
    return Point(vec.x, vec.y);
}

void AddShapeState::HandleEvent(Canvas *canvas)
{
    std::shared_ptr<IDrawableShape> newShape;

    switch (m_shape_type)

    {

    case SHAPES_TYPE::CIRCLE_T:

        newShape = std::make_shared<SFMLCircleAdapter>(Point(0, m_startPos.y), 50.0f);

        break;

    case SHAPES_TYPE::RECTANGLE_T:

        newShape = std::make_shared<SFMLRectangleAdapter>(
            Point(0, m_startPos.y),
            100.0f,
            100.0f);
        break;

    case SHAPES_TYPE::TRIANGLE_T:

        newShape = std::make_shared<SFMLTriangleAdapter>(
            Point(0, m_startPos.y),
            Point(0, m_startPos.y + 100),
            Point(100, m_startPos.y + 50));
        break;

    default:

        return;
    }

    canvas->ExecuteCommand(std::make_unique<AddShapeCommand>(canvas, newShape));
}