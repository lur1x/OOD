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
    void HandleEvent(Canvas *canvas, const sf::Event &event) override;
};