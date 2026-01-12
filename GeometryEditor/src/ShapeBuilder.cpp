#include "../include/ShapeBuilder.hpp"

void ShapeBuilder::Reset()
{
    m_type = SHAPES_TYPE::NONE;
    m_color = 0;
    m_outlineColor = 0;
    m_thickness = 0;
    m_radius = 0;

    m_position = m_center = {};
    m_p1 = m_p2 = m_p3 = {};
}

void ShapeBuilder::SetType(const SHAPES_TYPE &type)
{
    m_type = type;
}

void ShapeBuilder::SetPosition(const sf::Vector2f &position)
{
    m_position = position;
}

void ShapeBuilder::SetCircleData(const sf::Vector2f &center, float radius)
{
    m_center = center;
    m_radius = radius;
}

void ShapeBuilder::SetRectangleData(const sf::Vector2f &p1, const sf::Vector2f &p2)
{
    m_p1 = p1;
    m_p2 = p2;
}

void ShapeBuilder::SetTriangleData(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3)
{
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

void ShapeBuilder::SetCompositeData(const std::vector<std::shared_ptr<IDrawableShape>> &children)
{
    m_children = children;
}

void ShapeBuilder::SetOutlneColor(const uint32_t color)
{
    m_outlineColor = color;
}

void ShapeBuilder::SetOutlineThickness(const float thickness)
{
    m_thickness = thickness;
}

void ShapeBuilder::SetFillColor(const uint32_t color)
{
    m_color = color;
}

std::shared_ptr<IDrawableShape> ShapeBuilder::GetResult()
{
    std::shared_ptr<IDrawableShape> shape = nullptr;

    switch (m_type)
    {
    case SHAPES_TYPE::CIRCLE_T:
        shape = std::make_shared<SFMLCircleAdapter>(
            Point(m_center.x, m_center.y),
            m_radius);
        break;

    case SHAPES_TYPE::RECTANGLE_T:
        shape = std::make_shared<SFMLRectangleAdapter>(
            Point(m_p1.x, m_p1.y),
            m_p2.x,
            m_p2.y);
        break;

    case SHAPES_TYPE::TRIANGLE_T:
        shape = std::make_shared<SFMLTriangleAdapter>(
            Point(m_p1.x, m_p1.y),
            Point(m_p2.x, m_p2.y),
            Point(m_p3.x, m_p3.y));
        break;

    case SHAPES_TYPE::COMPOSITE_T:
    {
        auto group = std::make_shared<CompositeShape>();

        for (const auto &s : m_children)
        {
            group->Add(s);
            s->SetInGroup(true);
            m_unDrawChildren.push_back(s);
        }

        m_children.clear();

        return group;
    }

    default:
        return nullptr;
    }

    std::shared_ptr<sf::Shape> drawShape = shape->GetShape();

    drawShape->setPosition(m_position);
    drawShape->setFillColor(sf::Color(m_color));
    drawShape->setOutlineColor(sf::Color(m_outlineColor));
    drawShape->setOutlineThickness(m_thickness);

    return shape;
}

std::vector<std::shared_ptr<IDrawableShape>> ShapeBuilder::GetUndrawChildren()
{
    return m_unDrawChildren;
}