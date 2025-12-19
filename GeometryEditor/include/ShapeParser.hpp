#pragma once
#include "IShape.hpp"
#include "Constants.hpp"
#include "ShapeFactory.hpp"
#include <memory>
#include <vector>
#include <string>

class ShapeParser
{
public:
    static std::vector<std::unique_ptr<IShape>> ParseFile(const std::string &filename);
};