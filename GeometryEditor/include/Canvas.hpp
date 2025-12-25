#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawableShape.hpp"
#include "CompositeShape.hpp"

#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"
#include "ICommand.hpp"
#include "ITool.hpp"
#include "Constants.hpp"
class Canvas
{
public:
    Canvas(unsigned int width, unsigned int height, const std::string &title);

    bool IsOpen() const;
    void Draw();
    void AddShape(std::shared_ptr<IDrawableShape> shape);
    void ClearShapes();

    sf::Vector2f GetMousePosition() const;
    std::shared_ptr<IDrawableShape> GetShapeByHit(const sf::Vector2f &point) const;
    void ExecuteCommand(std::unique_ptr<ICommand> cmd);
    void SetTool(std::unique_ptr<ITool> tool);

private:
    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;

    std::vector<std::shared_ptr<IDrawableShape>> m_selected;
    bool m_dragging = false;

    sf::Vector2f m_lastMousePos;
    std::unique_ptr<ITool> m_tool;

    std::shared_ptr<IDrawableShape> HitTest(const sf::Vector2f &point);

    bool HandleEvents();

    void HandleMouseDragEvent(const sf::Event &event);
    void HandleGroupEvent(const sf::Event &event);
    void HandleDragEvent();
    void GroupSelectedShapes();
    void UngroupSelectedShapes();

    void AddNewShape(const sf::Event &event);
    void ChangeShape(const sf::Event &event);

    bool Render();
};