#pragma once
#include <fstream>
#include "Canvas.hpp"
#include "ShapeParser.hpp"
#include "ShapeFactory.hpp"

class Application
{
public:
    Application(const std::string &inputFile, const std::string &outputFile,
                unsigned int width, unsigned int height,
                const std::string &title);

    static Application &Instance()
    {
        static Application instance;
        return instance;
    }
    bool Run();

    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;

private:
    Application()
        : m_input(input::INPUT_FILENAME),
          m_output(input::OUTPUT_FILENAME),
          m_canvas(window::WIDTH_SIZE, window::HEIGHT_SIZE, window::TITLE) {};

    ~Application() = default;

    std::ifstream m_input;
    std::ofstream m_output;
    Canvas m_canvas;
};