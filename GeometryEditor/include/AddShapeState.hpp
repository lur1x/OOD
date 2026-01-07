#pragma once

#include <memory>
#include "ITool.hpp"
#include "AddShapeCommand.hpp"
#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"

class AddShapeState : public ITool
{
public:
    AddShapeState(const enum SHAPES_TYPE &shape_type, const sf::Vector2f &startPos)
        : m_shape_type(shape_type), m_startPos(startPos) {};
    void HandleEvent(Canvas *canvas) override;

private:
    enum SHAPES_TYPE m_shape_type;
    sf::Vector2f m_startPos;
};