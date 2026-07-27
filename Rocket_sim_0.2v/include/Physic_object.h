#pragma once
#include "Vector3D.h"
#include "System_numbers.h"
#include "Constants.h"



class Physic_object 
{
private:


protected:
    Vector3D position;
    double mass; //kg 
    const double C_D; //Коэффициент сопротивления
    const double AREA ; //  m2  upper surface
    Physic_object(Vector3D pos, double m, double c_d = 0, double area = 0) : position(pos), mass(m) , C_D(c_d) , AREA (area) {};
    virtual ~Physic_object() = default;

public:

    //getters
    double get_mass() const { return mass; }
    double get_AREA() const {return AREA;}
    double get_C_D() const {return C_D;}
    Vector3D get_position() const { return position ; } 
    Vector3D get_position_above_surface() const { return (position-Vector3D {0,RADIUS_E,0}); }
    


    //setters
    void reduce_mass(double amount) {mass-=amount;}
    void update_position(Vector3D& velocity , double pace) {position+=velocity*pace;}
    void set_position(Vector3D& pos) {position=pos;}
};


