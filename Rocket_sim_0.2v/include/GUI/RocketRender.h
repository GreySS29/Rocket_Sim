#pragma once
#include "../Rocket_components/Stage.h"
#include <vector>
#include <GL/glut.h>

class RocketRender {

   

    public:

    std::vector<std::pair<double,double>> trajectory;
    

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

    std::vector<std::pair<double,double>> get_max_min_traj (){

        double minX = trajectory[0].first, maxX = trajectory[0].first;
        double minY = trajectory[0].second, maxY = trajectory[0].second;

    for (const auto& p : trajectory) {
        if (p.first < minX) minX = p.first;
        if (p.first > maxX) maxX = p.first;
        if (p.second < minY) minY = p.second;
        if (p.second > maxY) maxY = p.second;
    }

    std::pair<double,double> min {minX,minY};
    std::pair<double,double> max {maxX,maxY};
    return  {min,max};
    
    }

    

    

    
};

   






    
    
    
  




