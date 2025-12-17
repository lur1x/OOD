
#pragma once
#include "SFMLCircleAdapter.hpp"
#include <memory>
#include <string>

class ShapeFactory
{
public:
    static std::unique_ptr<IShape> CreateShape(
        const std::string &type,
        const std::vector<float> &params);
};