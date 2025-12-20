#pragma once
#include "IDrawableShape.hpp"
#include "Constants.hpp"
#include "ShapeFactory.hpp"
#include <memory>
#include <vector>
#include <string>

class ShapeParser
{
public:
    static std::vector<std::shared_ptr<IDrawableShape>> ParseFile(std::ifstream &filename);
};