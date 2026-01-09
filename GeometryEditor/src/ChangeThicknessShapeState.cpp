#include "../include/ChangeThicknessShapeState.hpp"

void ChangeThicknessShapeState::HandleEvent(Canvas *canvas, const sf::Event &event)
{
    if (event.is<sf::Event::KeyPressed>() &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();
        const auto mousePos = canvas->GetMousePosition();
        const auto shape = canvas->GetShapeByHit(mousePos);

        if (!shape)
        {
            return;
        }
        const float thikness = shape->GetShape()->getOutlineThickness();

        if (keyEvent->scancode == sf::Keyboard::Scancode::Up)
        {
            canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(shape, thikness + 1));
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Down)
        {
            if (thikness - 1 > 0)
            {
                canvas->ExecuteCommand(std::make_unique<ChangeThicknessCommand>(shape, thikness - 1));
            }
        }
    }
}