#include "../include/DragState.hpp"

void DragState::HandleEvent(Canvas *canvas, const sf::Event &event)
{
    if (auto mousePress = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePress->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f clickPos = canvas->GetMousePosition();
            bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
            auto hit = canvas->HitTest(clickPos);

            if (hit)
            {
                if (!shift)
                {
                    canvas->ClearSelected();
                }

                canvas->SelectShape(hit);
                canvas->StartDragging(clickPos);
            }
            else if (!shift)
            {
                canvas->ClearSelected();
            }
        }
    }

    if (auto mouseRelease = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseRelease->button == sf::Mouse::Button::Left)
        {
            canvas->StopDragging();
        }
    }

    if (event.is<sf::Event::MouseMoved>() && canvas->IsDragging())
    {
        sf::Vector2f currPos = canvas->GetMousePosition();
        sf::Vector2f delta = currPos - canvas->GetLastMousePos();

        if (delta.x != 0 || delta.y != 0)
        {
            for (const auto &s : canvas->GetSelected())
            {
                canvas->ExecuteCommand(std::make_unique<DragCommand>(s, delta));
            }
            canvas->SetLastMousePos(currPos);
        }
    }
    if (auto keyPress = event.getIf<sf::Event::KeyPressed>())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
            {
                canvas->GroupSelected();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
            {
                canvas->UngroupSelected();
            }
        }
    }
}