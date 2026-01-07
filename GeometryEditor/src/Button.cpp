#include "../include/Button.hpp"

#include "../include/Button.hpp"

Button::Button(const sf::Vector2f &pos, const sf::Vector2f &size,
               const sf::String &textString, const sf::Font &font,
               const Action &action) : m_text(textString, font, 20),
                                       m_action(action)
{
    m_action = action;
    m_shape.setPosition(pos);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::White);

    m_text.setFillColor(sf::Color::Black);
    m_text.setString(textString);
    m_text.setCharacterSize(16);
    m_text.setFont(font);

    sf::FloatRect tb = m_text.getLocalBounds();
    m_text.setOrigin({tb.size.x * 0.5f, tb.size.y * 0.5f});
    m_text.setPosition({pos.x + size.x * 0.5f, pos.y + size.y * 0.5f});
}

void Button::Draw(sf::RenderWindow &window) const
{
    window.draw(m_shape);
    window.draw(m_text);
}

bool Button::IsMouseOver(const sf::RenderWindow &window) const
{
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

    const sf::Vector2f pos = m_shape.getPosition();
    const sf::Vector2f size = m_shape.getSize();

    return mousePos.x >= pos.x &&
           mousePos.y >= pos.y &&
           mousePos.x <= pos.x + size.x &&
           mousePos.y <= pos.y + size.y;
}

bool Button::IsClicked(const sf::RenderWindow &window, const sf::Event &event) const
{
    if (!IsMouseOver(window))
    {
        return false;
    }
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        auto mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        return mouseEvent->button == sf::Mouse::Button::Left;
    }

    return false;
}

Action Button::GetAction() const
{
    return m_action;
}