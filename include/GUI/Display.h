#pragma once
#include <vector>
#include <utility>
#include <string>
#include "RocketRender.h"

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

class Display {
public:
    enum class Mode { Auto, Manual, Live };

    explicit Display(RocketRender& render);
    static void setInstance(Display& d);
    static Display& instance();
    void setAnimationSpeed(double speed);
    void run(int argc, char** argv, Mode mode = Mode::Auto);

    void initLiveWindow(int width = 1200, int height = 800);
    bool renderLiveFrame(); 
    void closeLiveWindow();

    void startAnimation(); // Auto

private:
    Display() = delete;
    static Display* instancePtr;

    void createWindow(int width, int height, const char* title);

    void update();        // updateAuto()/updateManual() 
    void updateAuto();
    void updateManual();

    void display() const;

    static void framebufferSizeCallback(GLFWwindow* win, int width, int height);

    void drawGround(double x0, double x1) const;
    void drawHeightScale(double y0, double y1, double x) const;
    void drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const;
    void drawDataPanel(int panelWidth, int windowWidth, int windowHeight) const;
    std::string formatNumber(double value, int precision = 1) const;

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

    Mode mode = Mode::Auto;

    
    bool prevKeyRight = false;
    bool prevKeyLeft  = false;
    bool prevKeySpace = false;
};