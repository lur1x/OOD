#include "../../../../include/patterns/command/concrete/moving/DragCommand.hpp"

DragCommand::DragCommand(const std::vector<std::shared_ptr<IDrawableShape>> &shapes) : m_shapes(shapes)
{
    m_before.reserve(shapes.size());

    for (auto &s : shapes)
    {
        m_before.push_back(s->SaveState());
    }
}

void DragCommand::Execute()
{
    // m_shape->Move(m_delta);
}

void DragCommand::Undo()
{
    for (size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->RestoreState(m_before[i]);
    }
}