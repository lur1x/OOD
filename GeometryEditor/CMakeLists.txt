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
    src/CompositeShape.cpp
    src/AddShapeState.cpp
    src/ChangeColorShapeState.cpp
    src/ChangeThicknessShapeState.cpp
    src/ChangeColorCommand.cpp
    src/AddShapeCommand.cpp
    src/ChangeThicknessCommand.cpp
    src/DragCommand.cpp
    src/DragState.cpp
    src/Button.cpp
    src/Panel.cpp
    src/ChangeColorCommandFill.cpp
    src/ChangeColorThickness.cpp
    src/ColorChangeVisitor.cpp
    src/GroupShapesCommand.cpp
    src/OutlineColotChangeVisitor.cpp
    src/ShapeMemento.cpp
    src/ThicknessChangeVisitor.cpp
    src/UngroupShapesCommand.cpp
    src/BinaryShapeLoader.cpp
    src/BinaryShapeStrategy.cpp
    src/LoadBinState.cpp
    src/LoadCommand.cpp
    src/LoadTxtState.cpp
    src/ShapeBuilder.cpp
    src/ShapeLoader.cpp
    src/TxtShapeLoader.cpp
    src/TxtShapeStrategy.cpp
    src/SaveBinState.cpp
    src/SaveTxtState.cpp

)
configure_file(${CMAKE_SOURCE_DIR}/include/arialmt.ttf ${CMAKE_CURRENT_BINARY_DIR}/arialmt.ttf COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shapes.bin ${CMAKE_SOURCE_DIR}/shapes.bin COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shapes.txt ${CMAKE_SOURCE_DIR}/shapes.txt COPYONLY)

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