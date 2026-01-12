#include "../include/SFMLTriangleAdapter.hpp"

SFMLTriangleAdapter::SFMLTriangleAdapter(const Point &p1, const Point &p2, const Point &p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{

    m_triangle = std::make_shared<sf::ConvexShape>(3);

    m_triangle->setPoint(0, sf::Vector2f(p1.GetX(), p1.GetY()));
    m_triangle->setPoint(1, sf::Vector2f(p2.GetX(), p2.GetY()));
    m_triangle->setPoint(2, sf::Vector2f(p3.GetX(), p3.GetY()));
    m_triangle->setFillColor(sf::Color::Red);
    m_triangle->setOutlineColor(sf::Color::Black);
    m_triangle->setOutlineThickness(2.0f);
}

float SFMLTriangleAdapter::GetArea() const
{
    float a = m_p1.Distance(m_p2);
    float b = m_p2.Distance(m_p3);
    float c = m_p3.Distance(m_p1);
    float p = (a + b + c) / 2.0f;

    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float SFMLTriangleAdapter::GetPerimeter() const
{
    return m_p1.Distance(m_p2);
    +m_p2.Distance(m_p3) +
        m_p3.Distance(m_p1);
}

std::string SFMLTriangleAdapter::GetName() const
{
    return output::TRIANGLE;
}

std::string SFMLTriangleAdapter::ToString() const
{
    std::ostringstream oss;
    oss << GetName() << output::COLON + output::PERIMETER << std::fixed << std::setprecision(2) << GetPerimeter()
        << output::SEPARATOR + output::AREA << std::fixed << std::setprecision(2) << GetArea();
    return oss.str();
}

std::shared_ptr<sf::Shape> SFMLTriangleAdapter::GetShape() const
{
    return m_triangle;
}

bool SFMLTriangleAdapter::Contains(const sf::Vector2f &point) const
{
    sf::Vector2f v1 = m_triangle->getPoint(0);
    sf::Vector2f v2 = m_triangle->getPoint(1);
    sf::Vector2f v3 = m_triangle->getPoint(2);

    float denominator = ((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));

    if (std::fabs(denominator) < 1e-6)
    {
        return false;
    }

    float a = ((v2.y - v3.y) * (point.x - v3.x) + (v3.x - v2.x) * (point.y - v3.y)) / denominator;
    float b = ((v3.y - v1.y) * (point.x - v3.x) + (v1.x - v3.x) * (point.y - v3.y)) / denominator;
    float c = 1.0f - a - b;

    return (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1);
}

void SFMLTriangleAdapter::Move(const sf::Vector2f &delta)
{
    m_p1 = Point(m_p1.GetX() + delta.x, m_p1.GetY() + delta.y);
    m_p2 = Point(m_p2.GetX() + delta.x, m_p2.GetY() + delta.y);
    m_p3 = Point(m_p3.GetX() + delta.x, m_p3.GetY() + delta.y);

    m_triangle->setPoint(0, sf::Vector2f(m_p1.GetX(), m_p1.GetY()));
    m_triangle->setPoint(1, sf::Vector2f(m_p2.GetX(), m_p2.GetY()));
    m_triangle->setPoint(2, sf::Vector2f(m_p3.GetX(), m_p3.GetY()));
}

void SFMLTriangleAdapter::Accept(IShapeVisitor &visitor)
{
    visitor.Visit(*this);
}

std::vector<ShapeMemento> SFMLTriangleAdapter::SaveState() const
{
    std::vector<ShapeMemento> states(1);
    const std::shared_ptr<sf::Shape> s = m_triangle;

    states[0].SetFillColor(s->getFillColor());
    states[0].SetOutlineColor(s->getOutlineColor());
    states[0].SetThickness(s->getOutlineThickness());
    states[0].SetPosition(s->getPosition());

    return states;
}

void SFMLTriangleAdapter::RestoreState(const std::vector<ShapeMemento> &lastState)
{
    const std::shared_ptr<sf::Shape> s = m_triangle;

    s->setFillColor(lastState[0].GetFillColor());
    s->setOutlineColor(lastState[0].GetOutlineColor());
    s->setOutlineThickness(lastState[0].GetThickness());
    s->setPosition(lastState[0].GetPosition());
}

size_t SFMLTriangleAdapter::GetStateSize() const
{
    return 1;
}

void SFMLTriangleAdapter::SerializeToBinary(std::ostream &out) const
{
    const auto shape = m_triangle;
    SHAPES_TYPE type = SHAPES_TYPE::TRIANGLE_T;
    out.write(reinterpret_cast<const char *>(&type), sizeof(type));

    sf::Vector2f pos = shape->getPosition();
    out.write(reinterpret_cast<const char *>(&pos.x), sizeof(pos.x));
    out.write(reinterpret_cast<const char *>(&pos.y), sizeof(pos.y));

    Point p1 = m_p1, p2 = m_p2, p3 = m_p3;

    float p1X = m_p1.GetX();
    float p1Y = m_p1.GetY();
    float p2X = m_p2.GetX();
    float p2Y = m_p2.GetY();
    float p3X = m_p3.GetX();
    float p3Y = m_p3.GetY();
    out.write(reinterpret_cast<const char *>(&p1X), sizeof(p1X));
    out.write(reinterpret_cast<const char *>(&p1Y), sizeof(p1Y));
    out.write(reinterpret_cast<const char *>(&p2X), sizeof(p2X));
    out.write(reinterpret_cast<const char *>(&p2Y), sizeof(p2Y));
    out.write(reinterpret_cast<const char *>(&p3X), sizeof(p3X));
    out.write(reinterpret_cast<const char *>(&p3Y), sizeof(p3Y));

    uint32_t color = shape->getOutlineColor().toInteger();
    out.write(reinterpret_cast<const char *>(&color), sizeof(color));

    float thickness = shape->getOutlineThickness();
    out.write(reinterpret_cast<const char *>(&thickness), sizeof(thickness));

    uint32_t colorFill = shape->getFillColor().toInteger();
    out.write(reinterpret_cast<const char *>(&colorFill), sizeof(colorFill));
}

void SFMLTriangleAdapter::SerializeToText(std::ostream &out) const
{
    const auto shape = m_triangle;
    out << input::TRIANGLE << ' ';

    sf::Vector2f pos = shape->getPosition();
    out << pos.x << ' ' << pos.y << ' ';

    Point p1 = m_p1, p2 = m_p2, p3 = m_p3;
    out << p1.GetX() << ' ' << p1.GetY() << ' ' << p2.GetX() << ' ' << p2.GetY() << ' ' << p3.GetX() << ' ' << p3.GetY() << ' ';

    uint32_t color = shape->getOutlineColor().toInteger();
    float thickness = shape->getOutlineThickness();
    uint32_t colorFill = shape->getFillColor().toInteger();
    out << color << ' ' << thickness << ' ' << colorFill << '\n';
}