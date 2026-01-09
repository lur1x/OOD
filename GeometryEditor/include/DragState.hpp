#pragma once

#include "ITool.hpp"
#include "DragCommand.hpp"

class DragState : public ITool
{
public:
    DragState(const sf::Vector2f &startPos) : m_startPos(startPos) {};
    void HandleEvent(Canvas *canvas) override;

private:
    sf::Vector2f m_startPos;
};