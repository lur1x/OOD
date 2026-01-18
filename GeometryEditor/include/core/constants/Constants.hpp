#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <SFML/Graphics.hpp>

namespace window
{
    const unsigned int WIDTH_SIZE = 800;
    const unsigned int HEIGHT_SIZE = 500;
    const std::string TITLE = "Geometry Editor";
}

namespace input
{
    const std::string INPUT_FILENAME = "input.txt";
    const std::string OUTPUT_FILENAME = "output.txt";

    const std::string BIN_FILENAME = "shapes.bin";
    const std::string TEXT_FILENAME = "shapes.txt";
    const std::string FONT_FILENAME = "arialmt.ttf";

    const std::string RECTANGLE = "RECTANGLE";
    const std::string CIRCLE = "CIRCLE";
    const std::string TRIANGLE = "TRIANGLE";

    const std::string COMPOSITE = "COMPOSITE:";
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

    const std::string ATTEMPTING_LOAD_BIN = "Attempting to load from binary file: ";
    const std::string ATTEMPTING_LOAD_TXT = "Attempting to load from text file: ";
    const std::string SAVING_SHAPES_BIN = "Saving shapes to binary file: ";
    const std::string SAVING_SHAPES_TXT = "Saving shapes to text file: ";
    const std::string SHAPES_SAVED_SUCCESS = "Shapes saved successfully!";

}
namespace canvas
{
    const unsigned int FRAME_RATE = 60;
    const float SELECTION_FRAME_THICKNESS = 2.0f;
    const sf::Color BACKGROUND_COLOR = sf::Color::White;
    const sf::Color SELECTION_FRAME_COLOR = sf::Color::Green;
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
    TRIANGLE_T,
    COMPOSITE_T,
    NONE
};

const std::unordered_map<std::string, SHAPES_TYPE> SHAPES_MAP =
    {
        {input::RECTANGLE, SHAPES_TYPE::RECTANGLE_T},
        {input::CIRCLE, SHAPES_TYPE::CIRCLE_T},
        {input::TRIANGLE, SHAPES_TYPE::TRIANGLE_T},
        {input::COMPOSITE, SHAPES_TYPE::COMPOSITE_T}};

enum class Action
{
    SwitchMode,

    AddRectangle,
    AddTriangle,
    AddCircle,

    ColorRed,
    ColorBlue,
    ColorWhite,
    ColorBlack,

    FillColorRed,
    FillColorBlue,
    FillColorWhite,
    FillColorBlack,

    Thick1,
    Thick3,
    Thick5,

    LoadLastShapesBin,
    LoadLastShapesTxt,

    SaveShapesBin,
    SaveShapesTxt
};

const std::vector<std::pair<sf::String, Action>> BUTTONS =
    {
        {"Switch mode", Action::SwitchMode},

        {"Triangle", Action::AddTriangle},
        {"Rectangle", Action::AddRectangle},
        {"Circle", Action::AddCircle},

        {"Color red", Action::ColorRed},
        {"Color blue", Action::ColorBlue},
        {"Color white", Action::ColorWhite},
        {"Color black", Action::ColorBlack},

        {"Thick red", Action::FillColorRed},
        {"Thick blue", Action::FillColorBlue},
        {"Thick white", Action::FillColorWhite},
        {"Thick black", Action::FillColorBlack},

        {"Thickness 1", Action::Thick1},
        {"Thickness 3", Action::Thick3},
        {"Thickness 5", Action::Thick5},

        {"Load bin", Action::LoadLastShapesBin},
        {"Load txt", Action::LoadLastShapesTxt},

        {"Save bin", Action::SaveShapesBin},
        {"Save txt", Action::SaveShapesTxt}};