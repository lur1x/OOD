#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "Canvas.hpp"
#include "ShapeParser.hpp"
#include "ShapeFactory.hpp"

class Application
{
private:
    std::ifstream m_input;
    std::ofstream m_output;
    Canvas m_canvas;

public:
    Application(const std::string &inputFile, const std::string &outputFile,
                unsigned int width, unsigned int height,
                const std::string &title);

    bool run();

private:
    bool processInput();
    bool saveResults(const std::vector<std::unique_ptr<IShape>> &shapes);
};