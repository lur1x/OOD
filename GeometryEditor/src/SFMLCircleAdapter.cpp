#include "../include/SFMLCircleAdapter.hpp"

SFMLCircleAdapter::SFMLCircleAdapter(const Point &center, float radius)
    : m_center(center), m_radius(radius)
{

    m_circle = std::make_shared<sf::CircleShape>(radius);
    m_circle->setPosition(
        {m_center.GetX() - m_radius,
         m_center.GetY() - m_radius});

    m_circle->setFillColor(sf::Color::Green);
    m_circle->setOutlineColor(sf::Color::Black);
    m_circle->setOutlineThickness(2.0f);
}

float SFMLCircleAdapter::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

float SFMLCircleAdapter::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string SFMLCircleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

std::string SFMLCircleAdapter::GetName() const
{
    return output::CIRCLE;
}

std::shared_ptr<sf::Shape> SFMLCircleAdapter::GetShape() const
{
    return m_circle;
}

bool SFMLCircleAdapter::Contains(const sf::Vector2f &point) const
{
    return GetShape()->getGlobalBounds().contains(point);
}

void SFMLCircleAdapter::Move(const sf::Vector2f &delta)
{
    m_center = Point(m_center.GetX() + delta.x, m_center.GetY() + delta.y);

    m_circle->move(delta);
}

void SFMLCircleAdapter::Accept(IShapeVisitor &visitor)
{
    visitor.Visit(*this);
}

std::vector<ShapeMemento> SFMLCircleAdapter::SaveState() const
{
    std::vector<ShapeMemento> states(1);
    const std::shared_ptr<sf::Shape> s = m_circle;

    states[0].SetFillColor(s->getFillColor());
    states[0].SetOutlineColor(s->getOutlineColor());
    states[0].SetThickness(s->getOutlineThickness());
    states[0].SetPosition(s->getPosition());

    return states;
}

void SFMLCircleAdapter::RestoreState(const std::vector<ShapeMemento> &lastState)
{
    const std::shared_ptr<sf::Shape> s = m_circle;

    s->setFillColor(lastState[0].GetFillColor());
    s->setOutlineColor(lastState[0].GetOutlineColor());
    s->setOutlineThickness(lastState[0].GetThickness());
    s->setPosition(lastState[0].GetPosition());
}

size_t SFMLCircleAdapter::GetStateSize() const
{
    return 1;
}

void SFMLCircleAdapter::SerializeToBinary(std::ostream &out) const
{
    const auto shape = m_circle;
    SHAPES_TYPE type = SHAPES_TYPE::CIRCLE_T;
    out.write(reinterpret_cast<const char *>(&type), sizeof(type));

    sf::Vector2f pos = shape->getPosition();
    out.write(reinterpret_cast<const char *>(&pos.x), sizeof(pos.x));
    out.write(reinterpret_cast<const char *>(&pos.y), sizeof(pos.y));

    float centerX = m_center.GetX();
    float centerY = m_center.GetY();
    out.write(reinterpret_cast<const char *>(&centerX), sizeof(centerX));
    out.write(reinterpret_cast<const char *>(&centerY), sizeof(centerY));

    out.write(reinterpret_cast<const char *>(&m_radius), sizeof(m_radius));

    uint32_t color = shape->getOutlineColor().toInteger();
    out.write(reinterpret_cast<const char *>(&color), sizeof(color));

    float thickness = shape->getOutlineThickness();
    out.write(reinterpret_cast<const char *>(&thickness), sizeof(thickness));

    uint32_t colorFill = shape->getFillColor().toInteger();
    out.write(reinterpret_cast<const char *>(&colorFill), sizeof(colorFill));
}

void SFMLCircleAdapter::SerializeToText(std::ostream &out) const
{
    const auto shape = m_circle;
    out << input::CIRCLE << ' ';

    sf::Vector2f pos = shape->getPosition();
    out << pos.x << ' ' << pos.y << ' ' << m_center.GetX() << ' ' << m_center.GetY() << ' ' << m_radius << ' ';

    uint32_t color = shape->getOutlineColor().toInteger();
    float thickness = shape->getOutlineThickness();
    uint32_t colorFill = shape->getFillColor().toInteger();
    out << color << ' ' << thickness << ' ' << colorFill << '\n';
}