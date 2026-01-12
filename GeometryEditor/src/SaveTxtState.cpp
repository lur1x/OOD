#include "../include/SaveTxtState.hpp"
#include <iostream>

void SaveTxtState::HandleEvent(Canvas *canvas)
{
    std::cout << messages::SAVING_SHAPES_TXT << input::TEXT_FILENAME << std::endl;

    TxtShapeStrategy strategy;
    canvas->SaveToFile(input::TEXT_FILENAME, strategy);

    std::cout << messages::SHAPES_SAVED_SUCCESS << std::endl;
}