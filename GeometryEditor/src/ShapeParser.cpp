#include "../include/ShapeParser.hpp"
#include <fstream>
#include <iostream>

std::vector<std::unique_ptr<IShape>> ShapeParser::ParseFile(const std::string &filename)
{
    std::vector<std::unique_ptr<IShape>> shapes;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return shapes;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        try
        {
            std::string trimmed = Trim(line);
            if (trimmed.empty())
            {
                continue;
            }

            auto shape = ParseLine(trimmed);
            if (shape)
            {
                shapes.push_back(std::move(shape));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing line " << lineNumber << ": " << e.what()
                      << " (line: " << line << ")" << std::endl;
        }
    }

    file.close();
    return shapes;
}

std::unique_ptr<IShape> ShapeParser::ParseLine(const std::string &line)
{
    return ShapeFactory::CreateFromString(line);
}

std::string ShapeParser::Trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos)
    {
        return "";
    }

    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}