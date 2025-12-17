#include "include/IShape.hpp"
#include "include/SFMLCircleAdapter.hpp"
#include "include/ShapeParser.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

int main()
{
    try
    {
        std::vector<std::unique_ptr<IShape>> shapes =
            ShapeParser::ParseFile("../input.txt");

        if (shapes.empty())
        {
            std::cout << "No shapes loaded. Exiting." << std::endl;
            return 0;
        }

        std::cout << "Loaded " << shapes.size() << " shapes:" << std::endl;
        for (const auto &shape : shapes)
        {
            std::cout << shape->ToString() << std::endl;
        }

        std::ofstream output("../output.txt");
        if (output.is_open())
        {
            for (const auto &shape : shapes)
            {
                output << shape->ToString() << std::endl;
            }
            output.close();
            std::cout << "Results saved to output.txt" << std::endl;
        }

        sf::RenderWindow window(sf::VideoMode({800, 600}), "Geometric Shapes");
        window.setFramerateLimit(60);

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
                shape->Draw(window);
            }

            window.display();
        }

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}