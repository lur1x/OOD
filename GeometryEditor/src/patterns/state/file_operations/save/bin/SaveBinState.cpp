#include <iostream>

#include "../../../../../../include/patterns/state/concrete/file_operations/save/bin/SaveBinState.hpp"

void SaveBinState::HandleEvent(Canvas *canvas)
{
    std::cout << messages::SAVING_SHAPES_TXT << input::BIN_FILENAME << std::endl;

    BinaryShapeStrategy strategy;
    canvas->SaveToFile(input::BIN_FILENAME, strategy);

    std::cout << messages::SHAPES_SAVED_SUCCESS << std::endl;
}