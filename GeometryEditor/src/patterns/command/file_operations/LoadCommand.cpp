#include "../../../../include/patterns/command/concrete/file_operations/LoadCommand.hpp"

void LoadCommand::Execute()
{
}

void LoadCommand::Undo()
{
    m_canvas->ClearCanvas();

    for (auto &s : m_shapes)
    {
        m_canvas->AddShape(s);
    }
}