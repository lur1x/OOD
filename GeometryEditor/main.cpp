#include "./include/App.hpp"

int main()
{
    Application app("./input.txt", "./output.txt", 800, 600, "Geometric Shapes");
    return app.run() ? 0 : 1;
}