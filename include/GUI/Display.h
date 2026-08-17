#pragma once
#include <GL/glut.h>
#include <vector>
#include <utility>
#include "RocketRender.h"

class Display {
public:
    explicit Display(RocketRender& render);
    static void setInstance(Display& d);
    static Display& instance();
    void setAnimationSpeed(double speed);

    
    void run(int argc, char** argv);

    // для внешней логики:
    //void setTrajectory(const std::vector<std::pair<double,double>>& traj);
    void startAnimation();  // запускает таймер

private:
    Display() = delete;
    static Display* instancePtr;

    void display() const;
    //void animateDisplay() const;
    static void displayWrapper();
    static void timerWrapper(int);

    
    void drawGround(double x0, double x1) const;
    void drawHeightScale(double y0, double y1, double x) const;
    void drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const;

    RocketRender& rocket;
    double animationSpeed = 1.0; 
    size_t currentStep = 0;
    bool animating = false;
};