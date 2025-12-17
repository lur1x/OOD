#include "../include/ShapeParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

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
    while (std::getline(file, line))
    {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (!line.empty())
        {
            auto shape = ParseLine(line);
            if (shape)
            {
                shapes.push_back(std::move(shape));
            }
        }
    }

    file.close();
    return shapes;
}

std::unique_ptr<IShape> ShapeParser::ParseLine(const std::string &line)
{
    if (line.find("TRIANGLE:") == 0)
    {
        return ParseTriangle(line.substr(9));
    }
    else if (line.find("RECTANGLE:") == 0)
    {
        return ParseRectangle(line.substr(10));
    }
    else if (line.find("CIRCLE:") == 0)
    {
        return ParseCircle(line.substr(7));
    }

    return nullptr;
}

std::unique_ptr<IShape> ShapeParser::ParseCircle(const std::string &params)
{
    size_t cPos = params.find("C=");
    size_t rPos = params.find("R=");

    if (cPos == std::string::npos || rPos == std::string::npos)
    {
        return nullptr;
    }

    std::string centerStr = params.substr(cPos + 2, rPos - cPos - 3);
    Point center = ParsePoint(centerStr);

    std::string radiusStr = params.substr(rPos + 2);

    radiusStr.erase(std::remove_if(radiusStr.begin(), radiusStr.end(),
                                   [](char c)
                                   { return !std::isdigit(c) && c != '.'; }),
                    radiusStr.end());

    float radius = std::stof(radiusStr);

    return std::make_unique<SFMLCircleAdapter>(center, radius);
}

std::unique_ptr<IShape> ShapeParser::ParseRectangle(const std::string &params)
{
    // TODO: Реализовать для прямоугольника
    return nullptr;
}

std::unique_ptr<IShape> ShapeParser::ParseTriangle(const std::string &params)
{
    // TODO: Реализовать для треугольника
    return nullptr;
}

Point ShapeParser::ParsePoint(const std::string &pointStr)
{
    size_t commaPos = pointStr.find(',');
    if (commaPos == std::string::npos)
    {
        return Point();
    }

    float x = std::stof(pointStr.substr(0, commaPos));
    float y = std::stof(pointStr.substr(commaPos + 1));

    return Point(x, y);
}