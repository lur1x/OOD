#pragma once
#include "IDrawableShape.hpp"
#include "Constants.hpp"
#include "ShapeFactory.hpp"
#include <fstream>

class ShapeParser
{
public:
    static std::vector<std::shared_ptr<IDrawableShape>> ParseFile(std::ifstream &filename);
};