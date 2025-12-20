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

    bool Run();

private:
    std::ifstream m_input;
    std::ofstream m_output;
    Canvas m_canvas;
};