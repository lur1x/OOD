#include "../include/CompositeShape.hpp"
#include "../include/Constants.hpp"
#include <algorithm>

void CompositeShape::Add(const std::shared_ptr<IDrawableShape> &shape)
{
    m_shapes.push_back(shape);
}

void CompositeShape::Move(const sf::Vector2f &delta)
{
    for (auto &s : m_shapes)
    {
        s->Move(delta);
    }
}

bool CompositeShape::Contains(const sf::Vector2f &point) const
{
    for (auto &s : m_shapes)
    {
        if (s->Contains(point))
        {
            return true;
        }
    }

    return false;
}

std::shared_ptr<sf::Shape> CompositeShape::GetShape() const
{
    sf::FloatRect bounds = GetBounds();

    auto rect = std::make_shared<sf::RectangleShape>(bounds.size);
    rect->setPosition(bounds.position);
    rect->setFillColor(canvas::TRANSPARENT_COLOR);
    rect->setOutlineThickness(0);

    return rect;
}

const std::vector<std::shared_ptr<IDrawableShape>> &CompositeShape::GetShapes() const
{
    return m_shapes;
}

float CompositeShape::GetArea() const
{
    float sum = 0;
    for (auto &s : m_shapes)
    {
        sum += s->GetArea();
    }
    return sum;
}

float CompositeShape::GetPerimeter() const
{
    float sum = 0;
    for (auto &s : m_shapes)
    {
        sum += s->GetPerimeter();
    }
    return sum;
}

std::string CompositeShape::GetName() const
{
    return output::GROUP;
}

std::string CompositeShape::ToString() const
{
    std::string out = output::GROUP_START + output::NEWLINE;
    for (auto &s : m_shapes)
    {
        out += s->ToString() + output::NEWLINE;
    }
    return out + output::GROUP_END;
}

sf::FloatRect CompositeShape::GetBounds() const
{
    if (m_shapes.empty())
    {
        return sf::FloatRect();
    }
    sf::FloatRect bounds = m_shapes.front()->GetShape()->getGlobalBounds();

    for (auto &c : m_shapes)
    {

        sf::FloatRect child = c->GetShape()->getGlobalBounds();

        float left = std::min(bounds.position.x, child.position.x);
        float top = std::min(bounds.position.y, child.position.y);
        float right = std::max(bounds.position.x + bounds.size.x, child.position.x + child.size.x);
        float bottom = std::max(bounds.position.y + bounds.size.y, child.position.y + child.size.y);

        bounds = sf::FloatRect({left, top}, {right - left, bottom - top});
    }

    return bounds;
}