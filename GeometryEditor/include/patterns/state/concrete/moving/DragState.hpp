#pragma once

#include "../../base/IToolState.hpp"
#include "../../../command/concrete/moving/DragCommand.hpp"
#include "../../../command/concrete/grouping/GroupShapesCommand.hpp"
#include "../../../command/concrete/grouping/UngroupShapesCommand.hpp"

class DragState : public IToolState
{
public:
    DragState(const sf::Vector2f &startPos);

    void HandleEvent(Canvas *canvas) override;

private:
    sf::Vector2f m_startPos;
    bool isDragged;
    std::unique_ptr<DragCommand> m_activeCommand;
};