#pragma once

#include <fstream>

#include "../../base/IShapeStrategy.hpp"

class BinaryShapeStrategy : public IShapeStrategy
{
public:
    void Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename) override;
};
