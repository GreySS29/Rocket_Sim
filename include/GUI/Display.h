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
        // axes
    double viewMinX = 0.0, viewMaxX = 1.0;
    double viewMinY = 0.0, viewMaxY = 1.0;
    bool boundsFixed = false;
    static constexpr double targetHeight = 100000.0;

private:
    Display() = delete;
    static Display* instancePtr;

    void createWindow(int width, int height, const char* title);

    void update();        // updateAuto()/updateManual() 
    void updateAuto();
    void updateManual();

    void display() const;

    static void framebufferSizeCallback(GLFWwindow* win, int width, int height);

    void draw_target_line(double y, double x0, double x1) const;
    void drawText(double pixelX, double pixelY, const std::string& text,float r = 1.0f, float g = 1.0f, float b = 1.0f) const;
    void drawGround(double x0, double x1) const;
    void drawDataPanel(int panelWidth, int windowWidth, int windowHeight) const;
    std::string formatNumber(double value, int precision = 1) const;
    void setViewBounds(double minX, double maxX, double minY, double maxY);
    void computeBounds();
    void drawAxes(int panelWidth, int windowWidth, int windowHeight) const;



    void beginScreenSpace(int windowWidth, int windowHeight) const;
    void endScreenSpace() const;
    void worldToWindowPixel(double wx, double wy, double& px, double& py) const;

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