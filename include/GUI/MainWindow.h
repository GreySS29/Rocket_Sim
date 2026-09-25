#pragma once
#include <GLFW/glfw3.h>

class MainWindow {
public:
    
    enum class Choice { Exit, Auto, Manual, Live };

    MainWindow() = default;

    
    Choice run();

private:
    void init();
    void shutdown();

   
    void renderUI(bool& decided, Choice& choice);

    GLFWwindow* window = nullptr;
};