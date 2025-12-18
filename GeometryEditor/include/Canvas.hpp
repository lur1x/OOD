#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "IShape.hpp"

class Canvas
{
public:
    Canvas(unsigned int width, unsigned int height, const std::string &title);

    bool IsOpen() const;
    void Draw();
    void AddShape(std::unique_ptr<IShape> shape);
    void ClearShapes();

private:
    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<IShape>> m_shapes;

    bool HandleEvents();
    bool Render();
};