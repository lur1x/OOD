#pragma once
#include "IShape.hpp"
#include "SFMLCircleAdapter.hpp"
#include <memory>
#include <vector>
#include <string>

class ShapeParser
{
public:
    static std::vector<std::unique_ptr<IShape>> ParseFile(const std::string &filename);

private:
    static std::unique_ptr<IShape> ParseLine(const std::string &line);
    static std::unique_ptr<IShape> ParseCircle(const std::string &params);
    static std::unique_ptr<IShape> ParseRectangle(const std::string &params);
    static std::unique_ptr<IShape> ParseTriangle(const std::string &params);
    static Point ParsePoint(const std::string &pointStr);
};