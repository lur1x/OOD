#pragma once

#include <fstream>

#include "../../base/ShapeLoader.hpp"

class TxtShapeLoader : public ShapeLoader
{
public:
    using ShapeLoader::ShapeLoader;

private:
    std::string m_filename;
    std::ifstream m_file;
    SHAPES_TYPE m_type;

    std::shared_ptr<IDrawableShape> LoadShape();

protected:
    void BeginOpen(const std::string &filename) override;
    void ReadType() override;
    void ReadPosition() override;
    void ReadExtra() override;
    bool HasMore() override;
    void EndOpen() override;
};