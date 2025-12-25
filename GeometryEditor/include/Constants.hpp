#pragma once

#include <string>
#include <unordered_map>
namespace window
{
    const unsigned int WIDTH_SIZE = 800;
    const unsigned int HEIGHT_SIZE = 500;
    const std::string TITLE = "Geometry Editor";
}

namespace input
{
    const std::string INPUT_FILENAME = "../input.txt";
    const std::string OUTPUT_FILENAME = "../output.txt";

    const std::string RECTANGLE = "RECTANGLE";
    const std::string CIRCLE = "CIRCLE";
    const std::string TRIANGLE = "TRIANGLE";
}

namespace output
{
    const std::string COLON = ": ";
    const std::string PERIMETER = "P=";
    const std::string AREA = "S=";
    const std::string SEPARATOR = "; ";
    const std::string NEWLINE = "\n";
    const std::string GROUP_START = "Group: [";
    const std::string GROUP_END = "]";

    const std::string RECTANGLE = "RECTANGLE";
    const std::string CIRCLE = "CIRCLE";
    const std::string TRIANGLE = "TRIANGLE";
    const std::string GROUP = "Group";
}

namespace messages
{
    const std::string LOADING_SHAPES = "Loading shapes from file...";
    const std::string NO_SHAPES_LOADED = "No shapes loaded. Exiting.";
    const std::string LOADED_SHAPES_PREFIX = "Loaded ";
    const std::string LOADED_SHAPES_SUFFIX = " shapes.";
    const std::string STARTING_VISUALIZATION = "Starting visualization";

    const std::string ERROR_PREFIX = "Error: ";
    const std::string CANNOT_OPEN_INPUT_FILE = "Cannot open input file: ";
    const std::string CANNOT_OPEN_OUTPUT_FILE = "Cannot open output file: ";
    const std::string CANVAS_INITIALIZATION_FAILED = "Failed to initialize canvas (SFML window).";
    const std::string FILES_CLOSED_UNEXPECTEDLY = "Input or output files are closed unexpectedly.";

}
namespace canvas
{
    const unsigned int FRAME_RATE = 60;
    const float SELECTION_FRAME_THICKNESS = 2.0f;
    const sf::Color BACKGROUND_COLOR = sf::Color::White;
    const sf::Color SELECTION_FRAME_COLOR = sf::Color::Red;
    const sf::Color TRANSPARENT_COLOR = sf::Color::Transparent;
}

namespace colors
{
    const sf::Color CIRCLE_FILL_COLOR = sf::Color::Green;
    const sf::Color RECTANGLE_FILL_COLOR = sf::Color::Blue;
    const sf::Color TRIANGLE_FILL_COLOR = sf::Color::Red;
    const sf::Color SHAPE_OUTLINE_COLOR = sf::Color::Black;
    const float SHAPE_OUTLINE_THICKNESS = 2.0f;
}

enum class SHAPES_TYPE
{
    CIRCLE_T = 0,
    RECTANGLE_T,
    TRIANGLE_T
};

const std::unordered_map<std::string, SHAPES_TYPE> SHAPES_MAP =
    {
        {input::RECTANGLE, SHAPES_TYPE::RECTANGLE_T},
        {input::CIRCLE, SHAPES_TYPE::CIRCLE_T},
        {input::TRIANGLE, SHAPES_TYPE::TRIANGLE_T}};

enum class SHAPE_COLORS
{
    RED,
    BLUE,
    BLACK,
    WHITE,
    YELLOW,
    TRANSPARENT

};
enum class SHAPE_COLOR_CHANGE
{
    THICKNESS,
    FILL,
};

const int SHAPE_COLORS_SIZE = 6;

const std::unordered_map<SHAPE_COLORS, sf::Color> COLORS_MAP =
    {
        {SHAPE_COLORS::RED, sf::Color::Red},
        {SHAPE_COLORS::BLUE, sf::Color::Blue},
        {SHAPE_COLORS::BLACK, sf::Color::Black},
        {SHAPE_COLORS::WHITE, sf::Color::White},
        {SHAPE_COLORS::YELLOW, sf::Color::Yellow},
        {SHAPE_COLORS::TRANSPARENT, sf::Color::Transparent},
};