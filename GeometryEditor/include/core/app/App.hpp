#pragma once

#include <fstream>

#include "../canvas/Canvas.hpp"
#include "../../infrastructure/persistence/parser/ShapeParser.hpp"
#include "../../patterns/factory/ShapeFactory.hpp"

class App
{
public:
    App(const std::string &inputFile, const std::string &outputFile,
        unsigned int width, unsigned int height,
        const std::string &title);

    static App &Instance()
    {
        static App instance;
        return instance;
    }
    bool Run();

    App(const App &) = delete;
    App(App &&) = delete;

    App &operator=(const App &) = delete;
    App &operator=(App &&) = delete;

private:
    App()
        : m_input(input::INPUT_FILENAME),
          m_output(input::OUTPUT_FILENAME),
          m_canvas(window::WIDTH_SIZE, window::HEIGHT_SIZE, window::TITLE) {};

    ~App() = default;

    std::ifstream m_input;
    std::ofstream m_output;
    Canvas m_canvas;
};