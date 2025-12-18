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

bool Application::run()
{
    try
    {
        std::cout << "Loading shapes from file..." << std::endl;
        auto shapes = ShapeParser::parseFile("input.txt");

        if (shapes.empty())
        {
            std::cout << "No shapes loaded. Exiting." << std::endl;
            return false;
        }

        std::cout << "Loaded " << shapes.size() << " shapes." << std::endl;

        // Сохраняем результаты
        if (!saveResults(shapes))
        {
            return false;
        }

        // Добавляем фигуры в canvas
        for (auto &shape : shapes)
        {
            m_canvas.AddShape(std::move(shape));
        }

        std::cout << "Starting visualization. Press ESC to exit." << std::endl;
        m_canvas.Draw();

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

bool Application::processInput()
{
    // Этот метод теперь не используется, так как парсинг делается в ShapeParser
    return true;
}

bool Application::saveResults(const std::vector<std::unique_ptr<IShape>> &shapes)
{
    try
    {
        m_output << "=== Geometric Shapes Calculation Results ===\n\n";
        for (const auto &shape : shapes)
        {
            m_output << shape->ToString() << std::endl;
        }
        std::cout << "Results saved to output file." << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving results: " << e.what() << std::endl;
        return false;
    }
}