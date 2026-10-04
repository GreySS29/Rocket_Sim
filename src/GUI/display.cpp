#include "../../include/GUI/Display.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define STB_EASY_FONT_IMPLEMENTATION
#include "../../include/GUI/stb_easy_font.h"

Display::Display(RocketRender& render)
    : rocket(render)
{}

Display* Display::instancePtr = nullptr;

void Display::setInstance(Display& d) {
    instancePtr = &d;
}

Display& Display::instance() {
    return *instancePtr;
}

void Display::framebufferSizeCallback(GLFWwindow* /*win*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Display::createWindow(int width, int height, const char* title)
{
    if (!glfwInit()) {
        std::cerr << "GLFW: init failed\n";
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW: window creation failed\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void Display::startAnimation()
{
    if (rocket.trajectory.empty()) {
        return;
    }
    computeBounds();
    currentStep = 0;
    animating = true;
    lastStepTimestamp = glfwGetTime();
}

void Display::initLiveWindow(int width, int height)
{
    mode = Mode::Live;
    createWindow(width, height, "2D Rocket Flight - Live");

   
    glfwSwapInterval(0);

    currentStep = 0;
}

bool Display::renderLiveFrame()
{
    if (!window) {
        return false;
    }

    if (glfwWindowShouldClose(window)) {
        return false;
    }

    if (!rocket.trajectory.empty()) {
        currentStep = rocket.trajectory.size() - 1;
    }

    glfwPollEvents();
    computeBounds();
    display();
    glfwSwapBuffers(window);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    return !glfwWindowShouldClose(window);
}

void Display::closeLiveWindow()
{
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
    }
}

void Display::run(int /*argc*/, char** /*argv*/, Mode m) {
    mode = m;

    const char* title = (mode == Mode::Auto)
        ? "2D Rocket Flight - Auto"
        : "2D Rocket Flight - Manual (Left/Right, Space)";

    createWindow(1200, 800, title);

   
    startAnimation();

    while (!glfwWindowShouldClose(window)) {
        update();
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Display::update()
{
    if (mode == Mode::Auto) {
        updateAuto();
    } else {
        updateManual();
    }
}

void Display::updateAuto()
{
    if (!animating) {
        return;
    }

    const auto& traj = rocket.trajectory;
    const double stepDuration = 1.0 / animationSpeed;

    double now = glfwGetTime();
    while (now - lastStepTimestamp >= stepDuration) {
        if (currentStep + 1 < traj.size()) {
            ++currentStep;
            lastStepTimestamp += stepDuration;
        } else {
            animating = false;
            break;
        }
    }
}

void Display::updateManual()
{
    const auto& traj = rocket.trajectory;
    if (traj.empty()) {
        return;
    }

    const bool keySpace = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    const bool keyRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS
                       || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    const bool keyLeft  = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
                       || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;

    // Space 
    if (keySpace && !prevKeySpace) {
        animating = !animating;
        if (animating) {
            
            lastStepTimestamp = glfwGetTime();
        }
    }

    if (animating) {
        
        const double stepDuration = 1.0 / animationSpeed;
        double now = glfwGetTime();

        while (now - lastStepTimestamp >= stepDuration) {
            if (currentStep + 1 < traj.size()) {
                ++currentStep;
                lastStepTimestamp += stepDuration;
            } else {
                animating = false; 
                break;
            }
        }
    } else {
        
        if (keyRight && !prevKeyRight) {
            if (currentStep + 1 < traj.size()) {
                ++currentStep;
            }
        }

        if (keyLeft && !prevKeyLeft) {
            if (currentStep > 0) {
                --currentStep;
            }
        }
    }

    prevKeySpace = keySpace;
    prevKeyRight = keyRight;
    prevKeyLeft  = keyLeft;
}

void Display::setAnimationSpeed(double speed)
{
    animationSpeed = std::max(0.1, speed);
}

void Display::drawGround(double x0, double x1) const {
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(x0, 0.0);
    glVertex2d(x1, 0.0);
    glEnd();
}

void Display::draw_target_line(double y, double x0, double x1) const {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(x0, y);
    glVertex2d(x1, y);
    glEnd();
}

void Display::drawAxes(int panelWidth, int windowWidth, int windowHeight) const
{
    constexpr int ticks = 5;
    const float axisX = static_cast<float>(panelWidth) + 6.0f;   // фикс. пиксель по x
    const float axisY = static_cast<float>(windowHeight) - 24.0f; // фикс. пиксель по y

    struct Tick { double px, py; std::string label; };
    std::vector<Tick> yTicks, xTicks;

    // позиции считаем, пока активны проекция и viewport графика
    for (int i = 0; i <= ticks; ++i) {
        double h = viewMinY + (viewMaxY - viewMinY) * i / ticks;
        double px, py;
        worldToWindowPixel(viewMinX, h, px, py);
        yTicks.push_back({px, py, std::to_string(static_cast<int>(h))});

        double d = viewMinX + (viewMaxX - viewMinX) * i / ticks;
        worldToWindowPixel(d, viewMinY, px, py);
        xTicks.push_back({px, py, std::to_string(static_cast<int>(d))});
    }

    beginScreenSpace(windowWidth, windowHeight);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // оси
    glVertex2f(axisX, 0.0f);                       glVertex2f(axisX, static_cast<float>(windowHeight));
    glVertex2f(static_cast<float>(panelWidth), axisY);
    glVertex2f(static_cast<float>(windowWidth), axisY);
    // риски
    for (const auto& t : yTicks) {
        glVertex2f(axisX - 4.0f, static_cast<float>(t.py));
        glVertex2f(axisX + 4.0f, static_cast<float>(t.py));
    }
    for (const auto& t : xTicks) {
        glVertex2f(static_cast<float>(t.px), axisY - 4.0f);
        glVertex2f(static_cast<float>(t.px), axisY + 4.0f);
    }
    glEnd();

    // подписи (чёрные)
    for (const auto& t : yTicks)
        drawText(axisX + 8.0, t.py - 6.0, t.label + " m", 0.0f, 0.0f, 0.0f);
    for (const auto& t : xTicks)
        drawText(t.px - 10.0, axisY + 6.0, t.label, 0.0f, 0.0f, 0.0f);

    endScreenSpace();
}


void Display::beginScreenSpace(int windowWidth, int windowHeight) const
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glViewport(0, 0, windowWidth, windowHeight);
}

void Display::endScreenSpace() const
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Display::worldToWindowPixel(double wx, double wy, double& px, double& py) const
{
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLdouble winX = 0.0, winY = 0.0, winZ = 0.0;
    gluProject(wx, wy, 0.0, modelview, projection, viewport, &winX, &winY, &winZ);

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    px = winX;
    py = windowHeight - winY;
}

void Display::drawText(double pixelX, double pixelY, const std::string& text,
                       float r, float g, float b) const
{
    static char buffer[99999];
    const float scale = 1.6f;

    glPushMatrix();
    glTranslatef(static_cast<float>(pixelX), static_cast<float>(pixelY), 0.0f);
    glScalef(scale, scale, 1.0f);

    int numQuads = stb_easy_font_print(
        0.0f, 0.0f,
        const_cast<char*>(text.c_str()), nullptr,
        buffer, sizeof(buffer));

    glColor3f(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, numQuads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Display::setViewBounds(double minX, double maxX, double minY, double maxY)
{
    viewMinX = minX; viewMaxX = maxX;
    viewMinY = minY; viewMaxY = maxY;
    boundsFixed = true;   
}

void Display::computeBounds()
{
    if (boundsFixed || rocket.trajectory.empty()) return;

    const auto& traj = rocket.trajectory;
    double minX = traj.front().first, maxX = minX;
    double minY = traj.front().second, maxY = minY;

    for (const auto& p : traj) {
        minX = std::min(minX, p.first);
        maxX = std::max(maxX, p.first);
        minY = std::min(minY, p.second);
        maxY = std::max(maxY, p.second);
    }

    minY = std::min(minY, 0.0);
    maxY = std::max(maxY, targetHeight);

    const double mx = std::max(maxX - minX, 1.0) * 0.10;
    const double my = std::max(maxY - minY, 1.0) * 0.10;

    viewMinX = minX - mx;  viewMaxX = maxX + mx;
    viewMinY = minY - my;  viewMaxY = maxY + my;
}


std::string Display::formatNumber(double value, int precision) const
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}


//data panel

void Display::drawDataPanel(int panelWidth, int windowWidth, int windowHeight) const
{
    const auto& traj = rocket.trajectory;

    beginScreenSpace(windowWidth, windowHeight);

    
    glColor3f(0.12f, 0.12f, 0.16f);
    glBegin(GL_QUADS);
    glVertex2d(0.0, 0.0);
    glVertex2d(panelWidth, 0.0);
    glVertex2d(panelWidth, windowHeight);
    glVertex2d(0.0, windowHeight);
    glEnd();

    if (!traj.empty()) {
        const std::size_t idx = std::min(currentStep, traj.size() - 1);
        const double dt = 0.1;

        const double time     = static_cast<double>(idx) * dt / 10 ;
        const double height   = traj[idx].second;
        const double distance = traj[idx].first;

        double speed = rocket.velocity;
        double angle = rocket.angle;
        double mass = rocket.mass;

        std::string separate = rocket.separating ? "separated" : "booster exist";
    

        double x = 40.0;
        double y = 80.0;
        const double lineHeight = 40.0;

        drawText(x, y, "Rocket data");
        y += lineHeight + 8.0;

        drawText(x, y, "Time:     " + formatNumber(time) + " s");
        y += lineHeight;

        drawText(x, y, "Height:   " + formatNumber(height) + " m");
        y += lineHeight;

        drawText(x, y, "Distance: " + formatNumber(distance) + " m");
        y += lineHeight;

        drawText(x, y, "Speed:    " + formatNumber(speed) + " m/s");
        y += lineHeight;

        drawText(x, y, "Angle:    " + formatNumber(angle) + " *");
        y += lineHeight;

        drawText(x, y, "Mass:    " + formatNumber(mass) + " *");
        y += lineHeight;




        drawText(x, y, "Separate:    " + separate + " ");
        y += lineHeight;


        if (mode == Mode::Manual) {
            drawText(x, y, std::string("State:    ") + (animating ? "Playing" : "Paused"));
            y += lineHeight;
        }
    }

    endScreenSpace();
}

void Display::display() const
{
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const auto& traj = rocket.trajectory;
    if (traj.empty()) return;

    int windowWidth = 0, windowHeight = 0;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    const int panelWidth = std::min(260, windowWidth / 4);
    const int graphWidth = windowWidth - panelWidth;

    glViewport(panelWidth, 0, graphWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(viewMinX, viewMaxX, viewMinY, viewMaxY);   // фиксированные границы

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGround(viewMinX, viewMaxX);
    draw_target_line(targetHeight, viewMinX, viewMaxX);

    const std::size_t lastPoint = std::min(currentStep, traj.size() - 1);

    glColor3f(0.1f, 0.5f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (std::size_t i = 0; i <= lastPoint; ++i)
        glVertex2d(traj[i].first, traj[i].second);
    glEnd();

    const auto& current = traj[lastPoint];
    glColor3f(1.0f, 0.1f, 0.1f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2d(current.first, current.second);
    glEnd();

    // оси (ещё в viewport графика), затем панель
    drawAxes(panelWidth, windowWidth, windowHeight);
    drawDataPanel(panelWidth, windowWidth, windowHeight);
}