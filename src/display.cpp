#include "../include/GUI/Display.h"


Display* Display::Display::instance = nullptr;

void Display::drawGround(double x0,double x1) const
{
    glColor3f(0.0f, 0.5f, 0.0f);

    glBegin(GL_LINES);
    glVertex2d(x0, 0.0);
    glVertex2d(x1, 0.0);
    glEnd();
}

void Display::drawHeightScale(
    double y0,
    double y1,
    double x
) const
{
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2d(x, y0);
    glVertex2d(x, y1);
    glEnd();

    constexpr int ticks = 10;
    const double step = (y1 - y0) / ticks;

    for (int i = 0; i <= ticks; ++i) {
        const double h = y0 + step * i;

        glBegin(GL_LINES);
        glVertex2d(x - 2.0, h);
        glVertex2d(x + 2.0, h);
        glEnd();

        
        glRasterPos2d(x + 5.0, h - 2.0);

        const std::string label =
            std::to_string(static_cast<int>(h));

        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    }
};
void Display::drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const {
        if (pointCount == 0) return;

        glColor3f(0.0f, 0.0f, 0.0f);

        glBegin(GL_LINES);
        glVertex2f((float)x0, (float)y);
        glVertex2f((float)x1, (float)y);
        glEnd();

        const int ticks = 10;
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

            const std::string label = stream.str();

            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
            }
        }
};

 void Display::run(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(1200, 800);
        glutCreateWindow("2D Rocket Flight");

        glutDisplayFunc(displayWrapper);
        glutMainLoop();
};

 void Display::display() const
{
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const auto& trajectory = rocket.trajectory;

    if (trajectory.empty()) {
        glutSwapBuffers();
        return;
    }

    constexpr double dt = 1.0;

    const std::size_t pointCount = trajectory.size();


    const double timeMin = 0.0;
    const double timeMax =
        static_cast<double>(pointCount - 1) * dt;

    double heightMin = trajectory.front().second;
    double heightMax = trajectory.front().second;

    for (const auto& point : trajectory) {
        heightMin = std::min(heightMin, point.second);
        heightMax = std::max(heightMax, point.second);
    }

    double dx = (timeMax - timeMin) * 0.1 + 1.0;
    double dy = (heightMax - heightMin) * 0.1 + 1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(
        timeMin - dx,
        timeMax + dx,
        heightMin - dy,
        heightMax + dy
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const double leftX = timeMin - dx;
    const double bottomY = heightMin - dy;

    const double heightScaleX = leftX + dx * 0.2;
    const double timeScaleY = bottomY + dy * 0.08;

    drawGround(timeMin, timeMax);

    drawHeightScale(
        heightMin,
        heightMax,
        heightScaleX
    );

    drawTimeScale(
        pointCount,
        dt,
        timeMin,
        timeMax,
        timeScaleY
    );

    rocket.drawHeightOverTime(dt);

    glutSwapBuffers();
};