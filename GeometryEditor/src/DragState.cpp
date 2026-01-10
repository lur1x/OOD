#include "../include/DragState.hpp"

DragState::DragState(const sf::Vector2f &startPos)
    : m_startPos(startPos)
{
}

void DragState::HandleEvent(Canvas *canvas)
{
    auto eventOpt = canvas->GetEvent();

    if (!eventOpt)
    {
        return;
    }

    const sf::Event &event = *eventOpt;

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

    if (auto mouseRelease = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseRelease->button == sf::Mouse::Button::Left && canvas->IsDragging())
        {
            auto shapes = canvas->GetSelected();

            if (!shapes.empty())
            {
                m_activeCommand = std::make_unique<DragCommand>(shapes);
            }

            return;
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
                const sf::FloatRect bounds = s->GetShape()->getGlobalBounds();

                if (bounds.position.y + delta.y <= m_startPos.y || bounds.position.y + delta.y + bounds.size.y >= window::HEIGHT_SIZE)
                {
                    delta.y = 0;
                }

                if (bounds.position.x + delta.x <= 0 || bounds.position.x + delta.x + bounds.size.x >= window::WIDTH_SIZE)
                {
                    delta.x = 0;
                }

                s->Move(delta);

                if (delta.x != 0 || delta.y != 0)
                {
                    isDragged = true;
                }
            }

            canvas->SetLastMousePos(currPos);

            return;
        }
    }

    if (auto mousePress = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mousePress->button == sf::Mouse::Button::Left)
        {
            if (m_activeCommand && isDragged)
            {
                canvas->ExecuteCommand(std::move(m_activeCommand));
            }

            return;
        }
    }

    if (auto keyPress = event.getIf<sf::Event::KeyPressed>())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
            {
                canvas->ExecuteCommand(std::make_unique<GroupShapesCommand>(canvas));
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
            {
                canvas->ExecuteCommand(std::make_unique<UngroupShapesCommand>(canvas));
            }
        }
    }
}