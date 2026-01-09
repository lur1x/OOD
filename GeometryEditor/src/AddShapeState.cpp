#include "../include/AddShapeState.hpp"

Point ToPoint(const sf::Vector2f &vec)
{
    return Point(vec.x, vec.y);
}

void AddShapeState::HandleEvent(Canvas *canvas, const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();
        const sf::Vector2f mousePos = canvas->GetMousePosition();
        std::shared_ptr<IDrawableShape> newShape;

        if (keyEvent->scancode == sf::Keyboard::Scancode::Num1)
        {
            newShape = std::make_shared<SFMLCircleAdapter>(ToPoint(mousePos), 50);
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Num2)
        {
            const sf::Vector2f mousePosP2(mousePos.x, mousePos.y + 100);
            const sf::Vector2f mousePosP3(mousePos.x + 100, mousePos.y + 50);
            newShape = std::make_shared<SFMLTriangleAdapter>(
                ToPoint(mousePos),
                ToPoint(mousePosP2),
                ToPoint(mousePosP3));
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Num3)
        {
            const sf::Vector2f mousePosP2(mousePos.x + 100, mousePos.y + 100);
            Point topLeft = ToPoint(mousePos);
            float width = mousePosP2.x - mousePos.x;
            float height = mousePosP2.y - mousePos.y;
            newShape = std::make_shared<SFMLRectangleAdapter>(topLeft, width, height);
        }
        else
        {
            return;
        }
        canvas->ExecuteCommand(std::make_unique<AddShapeCommand>(canvas, newShape));
    }
}