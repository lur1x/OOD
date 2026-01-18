#include <iostream>

#include "../../../../../../include/patterns/state/concrete/file_operations/load/txt/LoadTxtState.hpp"

void LoadTxtState::HandleEvent(Canvas *canvas)
{
    std::cout << messages::ATTEMPTING_LOAD_TXT << input::TEXT_FILENAME << std::endl;

    ShapeBuilder builder;
    TxtShapeLoader loader(builder);

    auto shapes = loader.Load(input::TEXT_FILENAME);

    if (!shapes.empty())
    {
        auto prevShapes = canvas->GetShapes();
        canvas->ClearCanvas();

        for (auto &s : shapes)
        {
            canvas->AddShape(s);
        }
        canvas->ExecuteCommand(std::make_unique<LoadCommand>(canvas, prevShapes));
    }
    canvas->ClearTool();
}