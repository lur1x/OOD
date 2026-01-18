cmake_minimum_required(VERSION 3.15)
project(GeometryEditor)

set(CMAKE_CXX_STANDARD 17)

add_executable(GeometryEditor 
    src/main.cpp
    src/core/app/App.cpp
    src/core/canvas/Canvas.cpp
    src/domain/geometry/Point.cpp
    src/domain/shapes/adapter/composite/CompositeShape.cpp
    src/domain/shapes/adapter/primitive/circle/SFMLCircleAdapter.cpp
    src/domain/shapes/adapter/primitive/triangle/SFMLTriangleAdapter.cpp
    src/domain/shapes/adapter/primitive/rectangle/SFMLRectangleAdapter.cpp
    src/infrastructure/persistence/loader/base/ShapeLoader.cpp
    src/infrastructure/persistence/loader/concreate/bin/BinaryShapeLoader.cpp
    src/infrastructure/persistence/loader/concreate/txt/TxtShapeLoader.cpp
    src/infrastructure/persistence/parser/ShapeParser.cpp
    src/infrastructure/ui/widgets/button/Button.cpp
    src/infrastructure/ui/widgets/panel/Panel.cpp
    src/patterns/builder/ShapeBuilder.cpp
    src/patterns/command/creation/AddShapeCommand.cpp
    src/patterns/command/file_operations/LoadCommand.cpp
    src/patterns/command/grouping/GroupShapesCommand.cpp
    src/patterns/command/grouping/UngroupShapesCommand.cpp 
    src/patterns/command/modification/color/ChangeColorCommand.cpp
    src/patterns/command/modification/color/ChangeColorCommandFill.cpp
    src/patterns/command/modification/style/ChangeThicknessCommand.cpp
    src/patterns/command/moving/DragCommand.cpp
    src/patterns/factory/ShapeFactory.cpp
    src/patterns/memento/ShapeMemento.cpp
    src/patterns/state/creation/AddShapeState.cpp
    src/patterns/state/file_operations/load/bin/LoadBinState.cpp
    src/patterns/state/file_operations/load/txt/LoadTxtState.cpp
    src/patterns/state/file_operations/save/bin/SaveBinState.cpp
    src/patterns/state/file_operations/save/txt/SaveTxtState.cpp
    src/patterns/state/modification/color/ChangeColorShapeState.cpp
    src/patterns/state/modification/color/ChangeColorThicknessState.cpp
    src/patterns/state/modification/style/ChangeThicknessShapeState.cpp
    src/patterns/state/moving/DragState.cpp
    src/patterns/strategy/bin/BinaryShapeStrategy.cpp
    src/patterns/strategy/txt/TxtShapeStrategy.cpp
    src/patterns/visitor/color/ColorChangeVisitor.cpp
    src/patterns/visitor/color/OutlineColotChangeVisitor.cpp
    src/patterns/visitor/style/ThicknessChangeVisitor.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/resources/fonts/arialmt.ttf ${CMAKE_CURRENT_BINARY_DIR}/resources/fonts/arialmt.ttf COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/shapes.bin ${CMAKE_SOURCE_DIR}/data/shapes.bin COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/shapes.txt ${CMAKE_SOURCE_DIR}/data/shapes.txt COPYONLY)

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