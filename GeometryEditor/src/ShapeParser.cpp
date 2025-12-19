#include "../include/ShapeParser.hpp"
#include <fstream>

std::vector<std::unique_ptr<IShape>> ShapeParser::ParseFile(std::ifstream &file)
{
    std::vector<std::unique_ptr<IShape>> shapes;

    if (!file.is_open())
        return shapes;

    std::string line;

    while (std::getline(file, line))
    {
        size_t colonPos = line.find(output::COLON);
        if (colonPos == std::string::npos)
            continue;

        std::string type = line.substr(0, colonPos);
        std::string paramsStr = line.substr(colonPos + 1);

        std::stringstream ss(paramsStr);
        std::vector<float> params;
        float value;
        char comma;

        while (ss >> value)
        {
            params.push_back(value);
            if (!(ss >> comma))
                break;
        }

        if (auto it = SHAPES_MAP.find(type); it != SHAPES_MAP.end())
        {
            if (auto shape = ShapeFactory::CreateShape(it->second, params))
            {
                shapes.push_back(std::move(shape));
            }
        }
    }

    return shapes;
}