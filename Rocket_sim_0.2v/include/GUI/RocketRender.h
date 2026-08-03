#pragma once
#include "../Rocket_components/Stage.h"
#include <vector>
#include <GL/glut.h>

class RocketRender {

   

    public:

    std::vector<std::pair<double,double>> trajectory;
    static RocketRender* instance;

    RocketRender(){};

    void add_trajectory (double x, double y){
        trajectory.push_back(std::make_pair(x, y));
    }

    void print () const {
        for (std::pair x : trajectory)
        {
            std::cout<< "|" << x.first <<"  :  "<< x.second<< "|\t"; 
        }
    }

      void drawRocket() const {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glPopMatrix();
    }

    void drawTrajectory() const {
        if (trajectory.size() < 2) return;

        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : trajectory) {
            glVertex2f(static_cast<float>(p.first), static_cast<float>(p.second));
        }
        glEnd();
    }

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

    void drawHeightScale(double minY, double maxY) const {
    double x = 0.8;   // например, minX из твоего display() + небольшой отступ
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f((float)x, (float)minY);
    glVertex2f((float)x, (float)maxY);
    glEnd();

    double step = (maxY - minY) / 10.0;
    for (int i = 0; i <= 10; ++i) {
        double y = minY + step * i;

        glBegin(GL_LINES);
        glVertex2f((float)x - 2.0f, (float)y);
        glVertex2f((float)x + 2.0f, (float)y);
        glEnd();

        glRasterPos2f((float)x - 20.0f, (float)y - 2.0f);
        std::string label = std::to_string((int)y);
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
    }
}

    void display() const { //unlike rewrite! 
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    double minX = trajectory[0].first, maxX = trajectory[0].first;
    double minY = trajectory[0].second, maxY = trajectory[0].second;

    for (const auto& p : trajectory) {
        if (p.first < minX) minX = p.first;
        if (p.first > maxX) maxX = p.first;
        if (p.second < minY) minY = p.second;
        if (p.second > maxY) maxY = p.second;
    }

    double dx = (maxX - minX) * 0.1 + 1.0;
    double dy = (maxY - minY) * 0.1 + 1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(minX - dx, maxX + dx, minY - dy, maxY + dy);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGround();
    drawHeightScale(minY, maxY);
    drawTrajectory();
    drawRocket();

    glutSwapBuffers();
}






    static void displayWrapper() {
        if (instance) instance->display();
    }

    
    
  


};

