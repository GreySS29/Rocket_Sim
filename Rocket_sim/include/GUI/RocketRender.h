#pragma once
#include "../Rocket_components/Stage.h"
#include <vector>
#include <fstream>
#include <GL/glut.h>

using std::vector;
class RocketRender {

   

    public:

    vector<std::pair<double,double>> trajectory;
    vector<Vector3D> g_force;
    vector<Vector3D> a_force;
    vector<Vector3D> f_force;

    RocketRender(){};

    void add_trajectory (double x, double y){
        trajectory.push_back(std::make_pair(x, y));
    }

    void add_G_force (Vector3D& vec)
    {
        g_force.push_back(vec);
    }

       void add_A_force (Vector3D& vec)
    {
        a_force.push_back(vec);
    }

    void add_F_force (Vector3D& vec)
    {
        f_force.push_back(vec);
    }





    void put_force_buffer(std::ofstream& ofs)
    {
        if(g_force.size()!=a_force.size() && g_force.size()!=f_force.size() )
        {

            std::cerr << "sizes between g_force and a_force don't equal";
            return ;
        }
        for(size_t i =0; i<g_force.size(); ++i)
        {
            ofs << "G_force" << g_force[i] << "\t"
            << "A_force" << a_force[i] << '\t'
            << "F_force" << f_force[i] << '\n';
            

        }
    }

    void drawHeightOverTime(double dt) const
{
    if (trajectory.empty()) {
        return;
    }

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_STRIP);

    for (std::size_t i = 0; i < trajectory.size(); ++i) {
        const double time = static_cast<double>(i) * dt;
        const double height = trajectory[i].second;

        glVertex2d(time, height);
    }

    glEnd();
}






    void print () const {
        for (std::pair x : trajectory)
        {
            std::cout<< "|" << x.first <<"  :  "<< x.second<< "|\t"; 
        }
    }

    // void print (Vector3D vec) const {
    //     for (Vector3D p )
    // }

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

    // void draw_force(vector<Vector3D> force) const {
    //     if (force.size() < 2) 
    //     {
    //         std::cerr << "No data"<<'\n';
    //         return;
    //     }

    //     glColor3f(0.0f, 0.0f, 1.0f);
    //     glBegin(GL_LINE_STRIP);
    //     for (const auto& p : force) {
    //         glVertex2f(static_cast<float>(p.first), static_cast<float>(p.second));
    //     }
    //     glEnd();
    // }

    void drawTrajectory() const {
        if (trajectory.size() < 2) 
        {
            std::cerr << "No data"<<'\n';
            return;
        }
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

   






    
    
    
  




