#include <iostream>

#include "../../../../../../include/patterns/state/concrete/file_operations/save/txt/SaveTxtState.hpp"

void SaveTxtState::HandleEvent(Canvas *canvas)
{
    std::cout << messages::SAVING_SHAPES_TXT << input::TEXT_FILENAME << std::endl;

    TxtShapeStrategy strategy;
    canvas->SaveToFile(input::TEXT_FILENAME, strategy);

    std::cout << messages::SHAPES_SAVED_SUCCESS << std::endl;
}