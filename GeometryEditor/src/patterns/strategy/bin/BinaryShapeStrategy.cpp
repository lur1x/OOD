#include "../../../../include/patterns/strategy/concrete/bin/BinaryShapeStrategy.hpp"

void BinaryShapeStrategy::Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename)
{
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);

    if (out.good() && !shapes.empty())
    {
        for (auto &s : shapes)
        {
            if (!s->InGroup())
            {
                s->SerializeToBinary(out);
            }
        }
    }
}