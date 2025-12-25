#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawableShape.hpp"

#include "CompositeShape.hpp"
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

    std::vector<std::shared_ptr<IDrawableShape>> m_selected;
    bool m_dragging = false;

    sf::Vector2f m_lastMousePos;
    std::shared_ptr<IDrawableShape> HitTest(const sf::Vector2f &point);

    bool HandleEvents();

    void HandleMouseDragEvent(const sf::Event &event);
    void HandleGroupEvent(const sf::Event &event);
    void HandleDragEvent();
    void GroupSelectedShapes();
    void UngroupSelectedShapes();

    bool Render();
};