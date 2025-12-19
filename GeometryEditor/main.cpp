#include "./include/App.hpp"

int main()
{
    Application app("./input.txt", "./output.txt", 800, 600, "Geometric Editor");
    return app.Run() ? 0 : 1;
}