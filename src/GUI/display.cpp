
#include "../../include/GUI/Display.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
 

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
 
    // Код использует immediate mode (glBegin/glVertex...), поэтому
    // просим совместимый (не core) контекст.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
 
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW: window creation failed\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
 
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync
 
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}
 
void Display::startAnimation()
{
    if (rocket.trajectory.empty()) {
        return;
    }
 
    currentStep = 0;
    animating = true;
    lastStepTimestamp = glfwGetTime();
}
 
void Display::run(int /*argc*/, char** /*argv*/) {
    createWindow(1200, 800, "2D Rocket Flight");
 
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
 
// ---------------------------------------------------------------------
// Замена glutBitmapCharacter: рисуем текст поверх сцены в экранном
// (пиксельном) пространстве через stb_easy_font.
// ---------------------------------------------------------------------
 
void Display::beginScreenSpace(int windowWidth, int windowHeight) const
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // (0,0) — левый верхний угол окна, Y растёт вниз (удобно для текста)
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
    py = windowHeight - winY; // переводим Y из "снизу-вверх" в "сверху-вниз"
}
 
void Display::drawText(double pixelX, double pixelY, const std::string& text) const
{
    static char buffer[99999];
    int numQuads = stb_easy_font_print(
        static_cast<float>(pixelX), static_cast<float>(pixelY),
        const_cast<char*>(text.c_str()), nullptr,
        buffer, sizeof(buffer));
 
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, numQuads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}
 
void Display::drawHeightScale(double y0, double y1, double x) const {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(x, y0);
    glVertex2d(x, y1);
    glEnd();
 
    constexpr int ticks = 5;
    const double step = (y1 - y0) / ticks;
 
    std::vector<double> px(ticks + 1), py(ticks + 1);
    std::vector<std::string> labels(ticks + 1);
 
    for (int i = 0; i <= ticks; ++i) {
        double h = y0 + step * i;
 
        glBegin(GL_LINES);
        glVertex2d(x - 2.0, h);
        glVertex2d(x + 2.0, h);
        glEnd();
 
        worldToWindowPixel(x + 5.0, h - 2.0, px[i], py[i]);
        labels[i] = std::to_string(static_cast<int>(h));
    }
 
    int ww, wh;
    glfwGetFramebufferSize(window, &ww, &wh);
 
    beginScreenSpace(ww, wh);
    for (int i = 0; i <= ticks; ++i) {
        drawText(px[i], py[i], labels[i]);
    }
    endScreenSpace();
}
 
void Display::drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const {
    if (pointCount == 0) return;
 
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f((float)x0, (float)y);
    glVertex2f((float)x1, (float)y);
    glEnd();
 
    const int ticks = 5;
    double totalTime = (pointCount - 1) * dt;
    double stepTime = totalTime / ticks;
    double stepX = (x1 - x0) / ticks;
 
    std::vector<double> px(ticks + 1), py(ticks + 1);
    std::vector<std::string> labels(ticks + 1);
 
    for (int i = 0; i <= ticks; ++i) {
        double t = stepTime * i;
        double x = x0 + stepX * i;
 
        glBegin(GL_LINES);
        glVertex2f((float)x, (float)y - 2.0f);
        glVertex2f((float)x, (float)y + 2.0f);
        glEnd();
 
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << t;
        labels[i] = stream.str();
 
        worldToWindowPixel(x - 4.0, y - 6.0, px[i], py[i]);
    }
 
    int ww, wh;
    glfwGetFramebufferSize(window, &ww, &wh);
 
    beginScreenSpace(ww, wh);
    for (int i = 0; i <= ticks; ++i) {
        drawText(px[i], py[i], labels[i]);
    }
    endScreenSpace();
}
 
void Display::display() const
{
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
 
    const auto& traj = rocket.trajectory;
 
    if (traj.empty()) {
        return;
    }
 
    const double dt = 1.0;
 
    int windowWidth = 0, windowHeight = 0;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
 
    constexpr double mainFraction = 0.75;
 
    const int mainWidth  =
        static_cast<int>(windowWidth * mainFraction);
 
    const int graphWidth =
        windowWidth - mainWidth;
 
    // =========================================================
    // Левая часть: анимация положения ракеты X-Y
    // =========================================================
 
    glViewport(0, 0, mainWidth, windowHeight);
 
    double minX = traj.front().first;
    double maxX = traj.front().first;
    double minY = traj.front().second;
    double maxY = traj.front().second;
 
    for (const auto& point : traj) {
        minX = std::min(minX, point.first);
        maxX = std::max(maxX, point.first);
 
        minY = std::min(minY, point.second);
        maxY = std::max(maxY, point.second);
    }
 
    double rangeX = maxX - minX;
    double rangeY = maxY - minY;
 
    // Если ракета летит почти вертикально
    if (rangeX < 1.0) {
        rangeX = 1.0;
    }
 
    if (rangeY < 1.0) {
        rangeY = 1.0;
    }
 
    const double marginX = rangeX * 0.10;
    const double marginY = rangeY * 0.10;
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    gluOrtho2D(
        minX - marginX,
        maxX + marginX,
        minY - marginY,
        maxY + marginY
    );
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    // Земля
    glColor3f(0.0f, 0.5f, 0.0f);
 
    glBegin(GL_LINES);
    glVertex2d(minX - marginX, 0.0);
    glVertex2d(maxX + marginX, 0.0);
    glEnd();
 
    // Пройденная траектория
    glColor3f(0.1f, 0.5f, 1.0f);
 
    glBegin(GL_LINE_STRIP);
 
    const std::size_t lastPoint =
        std::min(currentStep, traj.size() - 1);
 
    for (std::size_t i = 0; i <= lastPoint; ++i) {
        glVertex2d(
            traj[i].first,
            traj[i].second
        );
    }
 
    glEnd();
 
    // Ракета
    const auto& current = traj[lastPoint];
 
    glColor3f(1.0f, 0.1f, 0.1f);
 
    glPointSize(10.0f);
 
    glBegin(GL_POINTS);
    glVertex2d(current.first, current.second);
    glEnd();
 
    // =========================================================
    // Правая часть: полный график высоты от времени
    // =========================================================
 
    glViewport(mainWidth, 0, graphWidth, windowHeight);
 
    const double timeMin = 0.0;
    const double timeMax =
        static_cast<double>(traj.size() - 1) * dt;
 
    const double heightMin = minY;
    const double heightMax = maxY;
 
    const double timeRange =
        std::max(timeMax - timeMin, 1.0);
 
    const double heightRange =
        std::max(heightMax - heightMin, 1.0);
 
    const double timeMargin   = timeRange * 0.10;
    const double heightMargin = heightRange * 0.10;
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    gluOrtho2D(
        timeMin - timeMargin,
        timeMax + timeMargin,
        heightMin - heightMargin,
        heightMax + heightMargin
    );
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    // Оси графика
    glColor3f(0.0f, 0.0f, 0.0f);
 
    glBegin(GL_LINES);
 
    // Ось времени
    glVertex2d(
        timeMin - timeMargin,
        0.0
    );
 
    glVertex2d(
        timeMax + timeMargin,
        0.0
    );
 
    // Ось высоты
    glVertex2d(
        0.0,
        heightMin - heightMargin
    );
 
    glVertex2d(
        0.0,
        heightMax + heightMargin
    );
 
    glEnd();
 
    // Полный график высоты от времени
    rocket.drawHeightOverTime(dt);
 
    // Текущая точка на графике
    const double currentTime =
        static_cast<double>(lastPoint) * dt;
 
    const double currentHeight =
        traj[lastPoint].second;
 
    glColor3f(1.0f, 0.0f, 0.0f);
 
    glPointSize(8.0f);
 
    glBegin(GL_POINTS);
    glVertex2d(currentTime, currentHeight);
    glEnd();
}