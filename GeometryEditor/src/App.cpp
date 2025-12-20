#include "../include/App.hpp"
#include <iostream>

Application::Application(const std::string &inputFile, const std::string &outputFile,
                         unsigned int width, unsigned int height,
                         const std::string &title)
    : m_input(inputFile), m_output(outputFile), m_canvas(width, height, title)
{
    try
    {
        if (!m_input.is_open())
        {
            throw std::runtime_error(messages::CANNOT_OPEN_INPUT_FILE + inputFile);
        }

        if (!m_output.is_open())
        {
            throw std::runtime_error(messages::CANNOT_OPEN_OUTPUT_FILE + outputFile);
        }
        if (!m_canvas.IsOpen())
        {
            throw std::runtime_error(messages::CANVAS_INITIALIZATION_FAILED);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << messages::ERROR_PREFIX << e.what() << std::endl;
        if (m_input.is_open())
        {
            m_input.close();
        }
        if (m_output.is_open())
        {
            m_output.close();
        }
        throw;
    }
}

bool Application::Run()
{
    try
    {
        std::cout << messages::LOADING_SHAPES << std::endl;
        auto shapes = ShapeParser::ParseFile(m_input);

        if (!m_input.is_open() || !m_output.is_open())
        {
            throw std::runtime_error(messages::FILES_CLOSED_UNEXPECTEDLY);
        }

        if (shapes.empty())
        {
            std::cout << messages::NO_SHAPES_LOADED << std::endl;
            return false;
        }

        std::cout << messages::LOADED_SHAPES_PREFIX << shapes.size() << messages::LOADED_SHAPES_SUFFIX << std::endl;

        for (auto &shape : shapes)
        {
            m_output << shape->ToString() << std::endl;
            m_canvas.AddShape(std::move(shape));
        }

        std::cout << messages::STARTING_VISUALIZATION << std::endl;
        m_canvas.Draw();

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << messages::ERROR_PREFIX << e.what() << std::endl;
        return false;
    }
}
