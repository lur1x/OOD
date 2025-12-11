#include "include/ShapeFactory.hpp"
#include "include/Point.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <cctype>

std::unique_ptr<CircleAdapter> parseCircle(const std::string &params)
{
    int cx, cy, r;

    if (sscanf(params.c_str(), "C=%d,%d; R=%d", &cx, &cy, &r) == 3)
    {
        return std::make_unique<CircleAdapter>(Point(static_cast<float>(cx), static_cast<float>(cy)), r);
    }

    return nullptr;
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::unique_ptr<IDrawableShape> parseLine(const std::string &line)
{
    std::string trimmed = trim(line);
    if (trimmed.empty())
        return nullptr;

    size_t colonPos = trimmed.find(':');
    if (colonPos == std::string::npos)
        return nullptr;

    std::string shapeType = trim(trimmed.substr(0, colonPos));
    std::string paramsStr = trim(trimmed.substr(colonPos + 1));

    if (shapeType == "CIRCLE")
    {
        return parseCircle(paramsStr);
    }

    return nullptr;
}

int main()
{
    std::vector<std::unique_ptr<IDrawableShape>> shapes;

    std::ifstream input("../input.txt");

    std::ofstream output("../output.txt");
    std::string line;
    while (std::getline(input, line))
    {
        auto shape = parseLine(line);
        if (shape)
        {
            shapes.push_back(std::move(shape));
        }
    }

    for (const auto &shape : shapes)
    {
        output << shape->ToString() << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Shapes");
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (const auto &shape : shapes)
        {
            window.draw(*shape->GetShape());
        }
        window.display();
    }

    return 0;
}