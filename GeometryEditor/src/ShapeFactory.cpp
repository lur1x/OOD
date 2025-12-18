#include "../include/ShapeFactory.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

std::unique_ptr<IShape> ShapeFactory::createShape(
    const std::string &type,
    const std::vector<float> &params)
{

    std::string upperType = toUpper(type);

    if (upperType == "CIRCLE")
    {
        if (params.size() != 3)
        {
            throw std::invalid_argument("Circle requires 3 parameters: centerX, centerY, radius");
        }
        return createCircle(Point(params[0], params[1]), params[2]);
    }
    else if (upperType == "RECTANGLE")
    {
        if (params.size() != 4)
        {
            throw std::invalid_argument("Rectangle requires 4 parameters: topLeftX, topLeftY, width, height");
        }
        return createRectangle(Point(params[0], params[1]), params[2], params[3]);
    }
    else if (upperType == "TRIANGLE")
    {
        if (params.size() != 6)
        {
            throw std::invalid_argument("Triangle requires 6 parameters: x1, y1, x2, y2, x3, y3");
        }
        return createTriangle(
            Point(params[0], params[1]),
            Point(params[2], params[3]),
            Point(params[4], params[5]));
    }

    throw std::invalid_argument("Unknown shape type: " + type);
}

std::unique_ptr<IShape> ShapeFactory::createFromString(const std::string &line)
{
    if (line.empty())
    {
        return nullptr;
    }

    size_t colonPos = line.find(':');
    if (colonPos == std::string::npos)
    {
        throw std::invalid_argument("Invalid format: missing ':'");
    }

    std::string type = line.substr(0, colonPos);
    std::string paramsStr = line.substr(colonPos + 1);

    // Убираем пробелы в начале и конце
    while (!type.empty() && std::isspace(type.front()))
        type.erase(0, 1);
    while (!type.empty() && std::isspace(type.back()))
        type.pop_back();

    while (!paramsStr.empty() && std::isspace(paramsStr.front()))
        paramsStr.erase(0, 1);
    while (!paramsStr.empty() && std::isspace(paramsStr.back()))
        paramsStr.pop_back();

    std::vector<float> params = parseParameters(paramsStr);
    return createShape(type, params);
}

std::unique_ptr<IShape> ShapeFactory::createCircle(const Point &center, float radius)
{
    return std::make_unique<SFMLCircleAdapter>(center, radius);
}

std::unique_ptr<IShape> ShapeFactory::createRectangle(const Point &topLeft, float width, float height)
{
    return std::make_unique<SFMLRectangleAdapter>(topLeft, width, height);
}

std::unique_ptr<IShape> ShapeFactory::createTriangle(const Point &p1, const Point &p2, const Point &p3)
{
    return std::make_unique<SFMLTriangleAdapter>(p1, p2, p3);
}

std::string ShapeFactory::toUpper(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::vector<float> ShapeFactory::parseParameters(const std::string &paramsStr)
{
    std::vector<float> params;
    std::stringstream ss(paramsStr);
    std::string token;

    // Удаляем все лишние символы, оставляем только числа и разделители
    std::string cleaned;
    for (char c : paramsStr)
    {
        if (std::isdigit(c) || c == '.' || c == ',' || c == ';' || c == '=')
        {
            cleaned += c;
        }
    }

    // Заменяем все разделители на пробелы
    std::replace(cleaned.begin(), cleaned.end(), ',', ' ');
    std::replace(cleaned.begin(), cleaned.end(), ';', ' ');
    std::replace(cleaned.begin(), cleaned.end(), '=', ' ');

    // Парсим числа
    std::stringstream cleanedSS(cleaned);
    float num;
    while (cleanedSS >> num)
    {
        params.push_back(num);
    }

    return params;
}

Point ShapeFactory::parsePoint(const std::string &pointStr)
{
    std::string cleaned = pointStr;
    std::replace(cleaned.begin(), cleaned.end(), ',', ' ');

    std::stringstream ss(cleaned);
    float x, y;
    ss >> x >> y;

    return Point(x, y);
}