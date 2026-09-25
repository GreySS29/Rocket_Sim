
#pragma once
#include <GLFW/glfw3.h>
 
#include "Display.h"
 
class MainWindow {
public:
    explicit MainWindow(Display& display);
 
    // Показывает окно с кнопками Start/Exit.
    // Возвращается только после того, как пользователь закрыл программу
    // (через Exit, крестик, или после завершения Display::run()).
    void run();
 
private:
    void init();
    void shutdown();
    void renderUI(bool& startPressed);
 
    GLFWwindow* window = nullptr;
    Display& display;
};
 