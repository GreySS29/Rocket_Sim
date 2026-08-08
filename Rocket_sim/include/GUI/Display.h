#pragma once
#include "RocketRender.h"
#include <iomanip>
#include <sstream>

class Display {
public:
    RocketRender& rocket;
    static Display* instance;

    Display(RocketRender& roc) : rocket(roc) {}

    void drawGround(double, double) const;
    void drawHeightScale(double y0, double y1, double x) const;
    void drawTimeScale(size_t pointCount, double dt, double x0, double x1, double y) const;
    void run(int argc, char** argv);
    void display() const;

    static void displayWrapper() {
        if (instance) instance->display();
    }
};