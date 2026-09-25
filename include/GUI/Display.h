#pragma once
#include <vector>
#include <utility>
#include <string>
#include "RocketRender.h"
 
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
 
class Display {
public:
    explicit Display(RocketRender& render);
    static void setInstance(Display& d);
    static Display& instance();
    void setAnimationSpeed(double speed);
 
    // argc/argv больше не нужны GLFW, сигнатура оставлена
    // для совместимости с существующим main().
    void run(int argc, char** argv);
 
    void startAnimation();  // запускает анимацию (таймер теперь считается в update())
 
private:
    Display() = delete;
    static Display* instancePtr;
 
    void createWindow(int width, int height, const char* title);
    void update();           // продвигает currentStep по реальному времени
    void display() const;    // отрисовка одного кадра
 
    static void framebufferSizeCallback(GLFWwindow* win, int width, int height);
 
    void drawGround(double x0, double x1) const;
    void drawHeightScale(double y0, double y1, double x) const;
    void drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const;
 
    // --- замена glutBitmapCharacter на stb_easy_font ---
    void beginScreenSpace(int windowWidth, int windowHeight) const;
    void endScreenSpace() const;
    void worldToWindowPixel(double wx, double wy, double& px, double& py) const;
    void drawText(double pixelX, double pixelY, const std::string& text) const;
 
    GLFWwindow* window = nullptr;
    RocketRender& rocket;
    double animationSpeed = 1.0;
    size_t currentStep = 0;
    bool animating = false;
    double lastStepTimestamp = 0.0;
};
 