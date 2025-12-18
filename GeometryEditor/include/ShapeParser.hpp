#pragma once
#include "IShape.hpp"
#include "ShapeFactory.hpp"
#include <memory>
#include <vector>
#include <string>

class ShapeParser
{
public:
    static std::vector<std::unique_ptr<IShape>> ParseFile(const std::string &filename);

private:
    static std::unique_ptr<IShape> ParseLine(const std::string &line);
    static std::string Trim(const std::string &str);
};