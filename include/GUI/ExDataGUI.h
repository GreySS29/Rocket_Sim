#pragma once
#include <string>


struct ExDataGUI
{

    double altitude {};
    double distance {} ; 
    double velocity {};
    double mass {};
    int angle {};


    ExDataGUI(){};

    void set_data(const double& al,const double& dis, const double& vel, const double& mas, const int& ang ) {
        altitude = al;
        distance = dis;
        velocity = vel;
        mass = mas;
        angle = ang;
    }

    std::string serializeExDataGUI() const {
        std::ostringstream oss;
        oss << "{"
            << "\"altitude\":" << altitude << ","
            << "\"distance\":" << distance << ","
            << "\"velocity\":" << velocity << ","
            << "\"mass\":" << mass << ","
            << "\"angle\":" << angle
            << "}\n";
        return oss.str();
    }

};

