#include "../../../../include/patterns/strategy/concrete/txt/TxtShapeStrategy.hpp"

void TxtShapeStrategy::Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename)
{
    std::ofstream out(filename);
    if (out.good() && !shapes.empty())
    {
        for (auto &s : shapes)
        {
            if (!s->InGroup())
            {
                s->SerializeToText(out);
            }
        }
    }
}