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

    const std::string RECT = "RECTANGLE";
    const std::string CIRCLE = "CIRCLE";
    const std::string TRIANGLE = "TRIANGLE";
}

namespace output
{
    const std::string COLON = ": ";
    const std::string PERIMETER = "P=";
    const std::string AREA = "S=";
    const std::string SEPARATOR = "; ";

    const std::string RECT = "RECTANGLE";
    const std::string CIRCLE = "CIRCLE";
    const std::string TRIANGLE = "TRIANGLE";
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

enum class SHAPES_TYPE
{
    CIRCLE_T = 0,
    RECTANGLE_T,
    TRIANGLE_T
};

const std::unordered_map<std::string, SHAPES_TYPE> SHAPES_MAP =
    {
        {input::RECT, SHAPES_TYPE::RECTANGLE_T},
        {input::CIRCLE, SHAPES_TYPE::CIRCLE_T},
        {input::TRIANGLE, SHAPES_TYPE::TRIANGLE_T}};