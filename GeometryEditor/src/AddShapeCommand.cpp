#include "../include/AddShapeCommand.hpp"

AddShapeCommand::AddShapeCommand(Canvas *canvas, std::shared_ptr<IDrawableShape> shape)
    : m_canvas(canvas), m_shape(shape)
{
}

void AddShapeCommand::Execute()
{
    m_canvas->AddShape(m_shape);
}

void AddShapeCommand::Undo()
{
    m_canvas->RemoveShape(m_shape);
}