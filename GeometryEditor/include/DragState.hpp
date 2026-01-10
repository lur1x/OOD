#pragma once

#include "ITool.hpp"
#include "DragCommand.hpp"
#include "GroupShapesCommand.hpp"
#include "UngroupShapesCommand.hpp"

class DragState : public ITool
{
public:
    DragState(const sf::Vector2f &startPos);

    void HandleEvent(Canvas *canvas) override;

private:
    sf::Vector2f m_startPos;
    bool isDragged;
    std::unique_ptr<DragCommand> m_activeCommand;
};