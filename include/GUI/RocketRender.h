#pragma once
#include "../Rocket_components/Stage.h"
#include <GL/gl.h>       // ← вместо glad
#include <GL/glu.h>
#include <vector>
#include <fstream>


using std::vector;
class RocketRender {

    public:

    vector<std::pair<double,double>> trajectory;
    vector<Vector3D> g_force;
    vector<Vector3D> a_force;
    vector<Vector3D> f_force;

    //constr
    RocketRender(){};

    //set
    void add_trajectory (double x, double y){trajectory.push_back(std::make_pair(x, y));}
    void add_G_force (Vector3D& vec){g_force.push_back(vec);}
    void add_A_force (Vector3D& vec){ a_force.push_back(vec);}
    void add_F_force (Vector3D& vec){f_force.push_back(vec);}

    vector<std::pair<double,double>> get_max_min_traj () const ; // will be not nessessary 


    void put_force_buffer(std::ofstream& ofs) const;
   

    void drawHeightOverTime(double dt) const;
    void drawRocket() const;
    void drawRocket(float x, float y) const;
    void drawTrajectory() const;


    void print_trajectory () const;



    



    

    

    
};

   






    
    
    
  




