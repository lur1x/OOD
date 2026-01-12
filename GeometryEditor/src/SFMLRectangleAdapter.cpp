#include "../include/SFMLRectangleAdapter.hpp"

SFMLRectangleAdapter::SFMLRectangleAdapter(const Point &topLeft, float width, float height)
    : m_topLeft(topLeft), m_width(width), m_height(height)
{

    m_rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
    m_rectangle->setPosition({topLeft.GetX(), topLeft.GetY()});
    m_rectangle->setFillColor(sf::Color::Blue);
    m_rectangle->setOutlineColor(sf::Color::Black);
    m_rectangle->setOutlineThickness(2.0f);
}

float SFMLRectangleAdapter::GetArea() const
{
    return m_width * m_height;
}

float SFMLRectangleAdapter::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string SFMLRectangleAdapter::GetName() const
{
    return output::RECTANGLE;
}

std::string SFMLRectangleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

std::shared_ptr<sf::Shape> SFMLRectangleAdapter::GetShape() const
{
    return m_rectangle;
}

bool SFMLRectangleAdapter::Contains(const sf::Vector2f &point) const
{
    m_rectangle->setPosition({m_topLeft.GetX(), m_topLeft.GetY()});

    sf::FloatRect bounds = m_rectangle->getGlobalBounds();
    return bounds.contains(point);
}

void SFMLRectangleAdapter::Move(const sf::Vector2f &delta)
{
    m_topLeft = Point(m_topLeft.GetX() + delta.x, m_topLeft.GetY() + delta.y);

    m_rectangle->move(delta);
}

void SFMLRectangleAdapter::Accept(IShapeVisitor &visitor)
{
    visitor.Visit(*this);
}

std::vector<ShapeMemento> SFMLRectangleAdapter::SaveState() const
{
    std::vector<ShapeMemento> states(1);

    const std::shared_ptr<sf::Shape> s = m_rectangle;

    states[0].SetFillColor(s->getFillColor());
    states[0].SetOutlineColor(s->getOutlineColor());
    states[0].SetThickness(s->getOutlineThickness());
    states[0].SetPosition(s->getPosition());

    return states;
}

void SFMLRectangleAdapter::RestoreState(const std::vector<ShapeMemento> &lastState)
{
    const std::shared_ptr<sf::Shape> s = m_rectangle;

    s->setFillColor(lastState[0].GetFillColor());
    s->setOutlineColor(lastState[0].GetOutlineColor());
    s->setOutlineThickness(lastState[0].GetThickness());
    s->setPosition(lastState[0].GetPosition());
}

size_t SFMLRectangleAdapter::GetStateSize() const
{
    return 1;
}

void SFMLRectangleAdapter::SerializeToBinary(std::ostream &out) const
{
    const auto shape = m_rectangle;
    SHAPES_TYPE type = SHAPES_TYPE::RECTANGLE_T;
    out.write(reinterpret_cast<const char *>(&type), sizeof(type));

    sf::Vector2f pos = shape->getPosition();
    out.write(reinterpret_cast<const char *>(&pos.x), sizeof(pos.x));
    out.write(reinterpret_cast<const char *>(&pos.y), sizeof(pos.y));

    float topLeftX = m_topLeft.GetX();
    float topLeftY = m_topLeft.GetY();

    out.write(reinterpret_cast<const char *>(&topLeftX), sizeof(topLeftX));
    out.write(reinterpret_cast<const char *>(&topLeftY), sizeof(topLeftY));

    out.write(reinterpret_cast<const char *>(&m_width), sizeof(m_width));
    out.write(reinterpret_cast<const char *>(&m_height), sizeof(m_height));

    uint32_t color = shape->getOutlineColor().toInteger();
    out.write(reinterpret_cast<const char *>(&color), sizeof(color));

    float thickness = shape->getOutlineThickness();
    out.write(reinterpret_cast<const char *>(&thickness), sizeof(thickness));

    uint32_t colorFill = shape->getFillColor().toInteger();
    out.write(reinterpret_cast<const char *>(&colorFill), sizeof(colorFill));
}

void SFMLRectangleAdapter::SerializeToText(std::ostream &out) const
{
    const auto shape = m_rectangle;
    out << input::RECTANGLE << ' ';

    sf::Vector2f pos = shape->getPosition();
    out << pos.x << ' ' << pos.y << ' ';
    out << m_topLeft.GetX() << ' ' << m_topLeft.GetY() << ' '
        << m_width << ' ' << m_height << ' ';

    uint32_t color = shape->getOutlineColor().toInteger();
    float thickness = shape->getOutlineThickness();
    uint32_t colorFill = shape->getFillColor().toInteger();
    out << color << ' ' << thickness << ' ' << colorFill << '\n';
}