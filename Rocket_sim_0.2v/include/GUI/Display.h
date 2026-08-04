#pragma once
#include "RocketRender.h"

class Display {
public:
    RocketRender& rocket;
    static Display* instance;

    Display(RocketRender& roc) : rocket(roc) {}

    void drawGround() const {
        glColor3f(0.0f, 0.5f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(-500.0f, 0.0f);
        glVertex2f(500.0f, 0.0f);
        glEnd();
    }

    void run(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(1200, 800);
        glutCreateWindow("2D Rocket Flight");

        glutDisplayFunc(displayWrapper);
        glutMainLoop();
    }

    void drawHeightScale(double y0, double y1, double x) const {
        glColor3f(0.0f, 0.0f, 0.0f);

        glBegin(GL_LINES);
        glVertex2f((float)x, (float)y0);
        glVertex2f((float)x, (float)y1);
        glEnd();

        const int ticks = 10;
        double step = (y1 - y0) / ticks;

        for (int i = 0; i <= ticks; ++i) {
            double h = y0 + step * i;

            glBegin(GL_LINES);
            glVertex2f((float)x - 2.0f, (float)h);
            glVertex2f((float)x + 2.0f, (float)h);
            glEnd();

            glRasterPos2f((float)(x - 30.0), (float)(h - 2.0));
            std::string label = std::to_string((int)h);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
            }
        }
    }

    void drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const {
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
            std::string label = std::to_string((int)t);
            for (char c : label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
            }
        }
    }

    void display() const {
        glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto bounds = rocket.get_max_min_traj();
        auto minP = bounds[0];
        auto maxP = bounds[1];

        double dx = (maxP.first - minP.first) * 0.1 + 1.0;
        double dy = (maxP.second - minP.second) * 0.1 + 1.0;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(minP.first - dx, maxP.first + dx,
                   minP.second - dy, maxP.second + dy);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        drawGround();

        double leftX = minP.first - dx;
        double bottomY = minP.second - dy;
        double heightScaleX = leftX + dx * 0.2;
        double timeScaleY = bottomY + dy * 0.08;

        drawHeightScale(minP.second, maxP.second, heightScaleX);
        drawTimeScale(rocket.trajectory.size(), 1, minP.first, maxP.first, timeScaleY); // 1 - rocket. dt 

        rocket.drawTrajectory();
        rocket.drawRocket();

        glutSwapBuffers();
    }

    static void displayWrapper() {
        if (instance) instance->display();
    }
};