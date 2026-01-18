#pragma once

#include <memory>

#include "../../base/IToolState.hpp"

#include "../../../command/concrete/creation/AddShapeCommand.hpp"

#include "../../../../domain/shapes/adapter/primitive/circle/SFMLCircleAdapter.hpp"
#include "../../../../domain/shapes/adapter/primitive/rectangle/SFMLRectangleAdapter.hpp"
#include "../../../../domain/shapes/adapter/primitive/triangle/SFMLTriangleAdapter.hpp"

class AddShapeState : public IToolState
{
public:
    AddShapeState(const enum SHAPES_TYPE &shape_type, const sf::Vector2f &startPos);

    void HandleEvent(Canvas *canvas) override;

private:
    enum SHAPES_TYPE m_shape_type;
    sf::Vector2f m_startPos;
};