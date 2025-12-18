#pragma once
#include "IShape.hpp"
#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class ShapeFactory
{
public:
    // Создание фигуры по типу и параметрам
    static std::unique_ptr<IShape> createShape(
        const std::string &type,
        const std::vector<float> &params);

    // Создание фигуры из строки (формат из файла)
    static std::unique_ptr<IShape> createFromString(const std::string &line);

    // Создание конкретных фигур
    static std::unique_ptr<IShape> createCircle(const Point &center, float radius);
    static std::unique_ptr<IShape> createRectangle(const Point &topLeft, float width, float height);
    static std::unique_ptr<IShape> createTriangle(const Point &p1, const Point &p2, const Point &p3);

private:
    static std::string toUpper(const std::string &str);
    static std::vector<float> parseParameters(const std::string &paramsStr);
    static Point parsePoint(const std::string &pointStr);
};