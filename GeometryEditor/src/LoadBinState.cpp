#include "../include/LoadBinState.hpp"
#include <iostream>

void LoadBinState::HandleEvent(Canvas *canvas)
{
    std::cout << messages::ATTEMPTING_LOAD_BIN << input::BIN_FILENAME << std::endl;

    ShapeBuilder builder;
    BinaryShapeLoader loader(builder);
    auto shapes = loader.Load(input::BIN_FILENAME);

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