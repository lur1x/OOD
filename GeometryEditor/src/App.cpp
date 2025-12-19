#include "../include/App.hpp"
#include <iostream>

Application::Application(const std::string &inputFile, const std::string &outputFile,
                         unsigned int width, unsigned int height,
                         const std::string &title)
    : m_input(inputFile), m_output(outputFile), m_canvas(width, height, title)
{

    if (!m_input.is_open())
    {
        throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    if (!m_output.is_open())
    {
        throw std::runtime_error("Cannot open output file: " + outputFile);
    }
}

bool Application::Run()
{
    try
    {
        std::cout << "Loading shapes from file..." << std::endl;
        auto shapes = ShapeParser::ParseFile("input.txt");

        if (shapes.empty())
        {
            std::cout << "No shapes loaded. Exiting." << std::endl;
            return false;
        }

        std::cout << "Loaded " << shapes.size() << " shapes." << std::endl;

        for (auto &shape : shapes)
        {
            m_output << shape->ToString() << std::endl;
            m_canvas.AddShape(std::move(shape));
        }

        std::cout << "Starting visualization" << std::endl;
        m_canvas.Draw();

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}
