
#pragma once
#include "CircleAdapter.hpp"
#include <memory>
#include <string>

class ShapeFactory
{
public:
    static std::unique_ptr<IDrawableShape> CreateShape(
        const std::string &type,
        const std::vector<float> &params);
};