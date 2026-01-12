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

void CompositeShape::Accept(IShapeVisitor &visitor)
{
    return;
}

std::vector<std::shared_ptr<IDrawableShape>> CompositeShape::GetAllShapes()
{
    std::vector<std::shared_ptr<IDrawableShape>> result;

    for (auto s : m_shapes)
    {
        CollectShapes(s, result);
    }

    return result;
}

void CompositeShape::CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes)
{
    auto group = std::dynamic_pointer_cast<CompositeShape>(shape);

    if (group)
    {
        for (const auto &s : group->GetShapes())
        {
            CollectShapes(s, outShapes);
        }
    }
    else
    {
        outShapes.push_back(shape);
    }
}

std::vector<ShapeMemento> CompositeShape::SaveState() const
{
    std::vector<ShapeMemento> result;
    result.reserve(GetStateSize());

    ShapeMemento own;
    result.push_back(own);

    for (auto &child : m_shapes)
    {
        auto cs = child->SaveState();

        result.insert(result.end(), cs.begin(), cs.end());
    }

    return result;
}

void CompositeShape::RestoreState(const std::vector<ShapeMemento> &lastState)
{
    size_t idx = 1;

    for (auto &child : m_shapes)
    {
        const size_t sz = child->GetStateSize();

        std::vector<ShapeMemento> sub(
            lastState.begin() + idx,
            lastState.begin() + idx + sz);

        child->RestoreState(sub);

        idx += sz;
    }
}

size_t CompositeShape::GetStateSize() const
{
    size_t sum = 1;

    for (auto &s : m_shapes)
    {
        sum += s->GetStateSize();
    }
    return sum;
}

void CompositeShape::SerializeToBinary(std::ostream &out) const
{
    auto shapes = GetShapes();

    SHAPES_TYPE type = SHAPES_TYPE::COMPOSITE_T;
    out.write(reinterpret_cast<const char *>(&type), sizeof(type));

    uint32_t count = static_cast<uint32_t>(shapes.size());
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));

    for (auto &s : shapes)
    {
        s->SerializeToBinary(out);
    }
}

void CompositeShape::SerializeToText(std::ostream &out) const
{
    auto shapes = GetShapes();
    out << input::COMPOSITE << ' ' << shapes.size() << ' ';

    for (auto &s : shapes)
    {
        s->SerializeToText(out);
    }
}