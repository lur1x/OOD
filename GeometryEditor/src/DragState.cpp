#include "../include/DragState.hpp"

void DragState::HandleEvent(Canvas *canvas)
{

    auto optEvent = canvas->GetEvent();
    if (!optEvent)
        return;

    const sf::Event event = *optEvent;
    if (event.is<sf::Event::MouseButtonReleased>() &&
        event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
    {
        canvas->StopDragging();
    }
    if (event.is<sf::Event::MouseMoved>() && canvas->IsDragging())
    {
        sf::Vector2f currPos = canvas->GetMousePosition();
        sf::Vector2f delta = currPos - canvas->GetLastMousePos();

        if (delta.x > 10 && delta.y > 10)
        {
            return;
        }

        for (const auto &s : canvas->GetSelected())
        {
            canvas->ExecuteCommand(std::make_unique<DragCommand>(s, delta));
        }
        canvas->SetLastMousePos(currPos);
    }

    if (event.is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
    {
        auto keyEvent = event.getIf<sf::Event::KeyPressed>();
        if (keyEvent->scancode == sf::Keyboard::Scancode::G)
        {
            canvas->GroupSelected();
        }
        if (keyEvent->scancode == sf::Keyboard::Scancode::U)
        {
            canvas->UngroupSelected();
        }
    }
}