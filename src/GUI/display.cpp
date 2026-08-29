#include "../../include/GUI/Display.h"
#include <algorithm>
#include <sstream>
#include <iomanip>


Display::Display(RocketRender& render)
    : rocket(render)
    , currentStep(0)
    , animating(false)
{}


Display* Display::instancePtr = nullptr;

void Display::setInstance(Display& d) {
    instancePtr = &d;
}

Display& Display::instance() {
    return *instancePtr;
}

// void Display::setTrajectory(const std::vector<std::pair<double,double>>& traj) {
//     rocket.trajectory = traj;
// }

void Display::startAnimation()
{
    if (rocket.trajectory.empty()) {
        return;
    }

    currentStep = 0;
    animating = true;

    const int delayMs = static_cast<int>(
        1000.0 / animationSpeed
    );

    glutTimerFunc(delayMs, timerWrapper, 0);
}

void Display::run(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("2D Rocket Flight");

    glutDisplayFunc(displayWrapper);

    startAnimation();
    glutMainLoop();
}

void Display::displayWrapper() {
    Display::instance().display();
}

void Display::timerWrapper(int)
{
    auto& d = Display::instance();

    if (!d.animating) {
        return;
    }

    const auto& traj = d.rocket.trajectory;

    if (d.currentStep + 1 < traj.size()) {
        ++d.currentStep;

        glutPostRedisplay();

        const int delayMs = static_cast<int>(
            1000.0 / d.animationSpeed
        );

        glutTimerFunc(delayMs, timerWrapper, 0);
    }
    else {
        d.animating = false;
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

void Display::drawHeightScale(double y0, double y1, double x) const {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(x, y0);
    glVertex2d(x, y1);
    glEnd();

    constexpr int ticks = 5;
    const double step = (y1 - y0) / ticks;

    for (int i = 0; i <= ticks; ++i) {
        double h = y0 + step * i;

        glBegin(GL_LINES);
        glVertex2d(x - 2.0, h);
        glVertex2d(x + 2.0, h);
        glEnd();

        glRasterPos2d(x + 5.0, h - 2.0);
        std::string label = std::to_string(static_cast<int>(h));
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    }
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

    for (int i = 0; i <= ticks; ++i) {
        double t = stepTime * i;
        double x = x0 + stepX * i;

        glBegin(GL_LINES);
        glVertex2f((float)x, (float)y - 2.0f);
        glVertex2f((float)x, (float)y + 2.0f);
        glEnd();

        glRasterPos2f((float)(x - 4.0), (float)(y - 6.0));
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << t;
        std::string label = stream.str();

        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    }
}

void Display::display() const
{
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const auto& traj = rocket.trajectory;

    if (traj.empty()) {
        glutSwapBuffers();
        return;
    }

    const double dt = 1.0;

    const int windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
    const int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

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

    glutSwapBuffers();
}