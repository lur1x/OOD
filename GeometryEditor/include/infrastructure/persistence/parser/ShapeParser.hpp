#pragma once

#include <fstream>

#include "../../../domain/shapes/adapter/base/IDrawableShape.hpp"
#include "../../../core/constants/Constants.hpp"
#include "../../../patterns/factory/ShapeFactory.hpp"

class ShapeParser
{
public:
    static std::vector<std::shared_ptr<IDrawableShape>> ParseFile(std::ifstream &filename);
};