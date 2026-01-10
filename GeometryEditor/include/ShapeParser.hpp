#pragma once

#include <fstream>

#include "IDrawableShape.hpp"
#include "Constants.hpp"
#include "ShapeFactory.hpp"

class ShapeParser
{
public:
    static std::vector<std::shared_ptr<IDrawableShape>> ParseFile(std::ifstream &filename);
};