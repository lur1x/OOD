#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawableShape.hpp"
#include "CompositeShape.hpp"

#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"

#include "Constants.hpp"
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

    void AddNewShape(const sf::Event &event);
    void ChangeShape(const sf::Event &event);

    sf::Color GetNextColor(const sf::Color &colorShape) const;
    SHAPE_COLORS GetEnumFromColor(const sf::Color &color) const;

    bool Render();
};