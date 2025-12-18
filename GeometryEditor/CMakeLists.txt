cmake_minimum_required(VERSION 3.15)
project(GeometryEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(GeometryEditor 
    main.cpp
    src/Point.cpp
    src/SFMLCircleAdapter.cpp
    src/ShapeParser.cpp
    src/ShapeFactory.cpp
    src/App.cpp
    src/Canvas.cpp
    src/SFMLTriangleAdapter.cpp
    src/SFMLRectangleAdapter.cpp
    
)

target_compile_definitions(GeometryEditor PRIVATE SFML_STATIC)

target_include_directories(GeometryEditor PRIVATE 
    "C:/Users/mrlur/Documents/study/libraries/SFML-3.0.2/include"
)

target_link_directories(GeometryEditor PRIVATE
    "C:/Users/mrlur/Documents/study/libraries/SFML-3.0.2/lib"
)

target_link_libraries(GeometryEditor
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    opengl32
    freetype
    winmm
    gdi32
)