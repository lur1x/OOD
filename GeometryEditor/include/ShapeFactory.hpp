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
    static std::unique_ptr<IShape> CreateShape(
        const std::string &type,
        const std::vector<float> &params);

    static std::unique_ptr<IShape> CreateFromString(const std::string &line);

    static std::unique_ptr<IShape> CreateCircle(const Point &center, float radius);
    static std::unique_ptr<IShape> CreateRectangle(const Point &topLeft, float width, float height);
    static std::unique_ptr<IShape> CreateTriangle(const Point &p1, const Point &p2, const Point &p3);

private:
    static std::string ToUpper(const std::string &str);
    static std::vector<float> ParseParameters(const std::string &paramsStr);
    static Point ParsePoint(const std::string &pointStr);
};