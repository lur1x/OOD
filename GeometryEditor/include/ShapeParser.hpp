#pragma once
#include "IShape.hpp"
#include "ShapeFactory.hpp"
#include <memory>
#include <vector>
#include <string>

class ShapeParser
{
public:
    static std::vector<std::unique_ptr<IShape>> parseFile(const std::string &filename);

private:
    static std::unique_ptr<IShape> parseLine(const std::string &line);
    static std::string trim(const std::string &str);
};