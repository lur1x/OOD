#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawableShape.hpp"
#include "CompositeShape.hpp"
#include "SFMLCircleAdapter.hpp"
#include "SFMLRectangleAdapter.hpp"
#include "SFMLTriangleAdapter.hpp"
#include "ICommand.hpp"
#include "ITool.hpp"
#include "Panel.hpp"
#include <optional>
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
    std::shared_ptr<IDrawableShape> HitTest(const sf::Vector2f &point) const;
    std::vector<std::shared_ptr<IDrawableShape>> GetAllSelectedShapes();
    void ExecuteCommand(std::unique_ptr<ICommand> cmd);
    void ClearSelected();

    void StartDragging(const sf::Vector2f &pos);
    void StopDragging();
    bool IsDragging() const;

    void SetLastMousePos(const sf::Vector2f &pos);
    sf::Vector2f GetLastMousePos() const;

    void GroupSelected();
    void UngroupSelected();

    void SelectShape(const std::shared_ptr<IDrawableShape> &shape);

    std::vector<std::shared_ptr<IDrawableShape>> GetSelected() const;

    std::optional<sf::Event> GetEvent() const;

private:
    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<IDrawableShape>> m_shapes;

    std::vector<std::shared_ptr<IDrawableShape>> m_selected;
    bool m_dragging = false;

    sf::Vector2f m_lastMousePos;
    std::unique_ptr<ITool> m_tool;
    Panel m_panel;
    std::optional<sf::Event> m_event;

    void SetEvent(const sf::Event &event);
    void SetTool(std::unique_ptr<ITool> tool);

    void ClearTool();

    bool HandleEvents();

    // void GroupSelectedShapes();
    // void UngroupSelectedShapes();

    bool Render();

    sf::RectangleShape RenderFrame(const sf::FloatRect &bounds) const;

    void SelectEvent(const sf::Event &event);

    void CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes);
};