#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawableShape.hpp"

class Canvas
{
public:
    Canvas(unsigned int width, unsigned int height, const std::string &title);

    bool IsOpen() const;
    void Draw();
    void AddShape(std::shared_ptr<IDrawableShape> shape);
    void ClearShapes();

private:
    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;

    bool HandleEvents();
    bool Render();
};