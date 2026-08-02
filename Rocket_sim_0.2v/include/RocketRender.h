#pragma once
#include "Rocket_components/Stage.h"
#include <vector>

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
    
  


};