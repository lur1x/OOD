#include "./include/App.hpp"

int main()
{
    Application app(input::INPUT_FILENAME, input::OUTPUT_FILENAME, window::WIDTH_SIZE, window::HEIGHT_SIZE, window::TITLE);
    return app.Run() ? 0 : 1;
}