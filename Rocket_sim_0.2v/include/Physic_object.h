#pragma once
#include "Vector3D.h"
#include "Constants.h"



class Physic_object 
{
private:


protected:
    Vector3D position;
    double mass; //kg 
    const double c_d; //Коэффициент сопротивления
    const double area ; //  m2  upper surface
    Physic_object(Vector3D pos, double m, double cd = 0, double ar = 0) : position(pos), mass(m) , c_d(cd) , area (ar) {};
    virtual ~Physic_object() = default;

public:

    //getters
    double get_mass() const { return mass; }
    double get_AREA() const {return area;}
    double get_C_D() const {return c_d;}
    Vector3D get_position() const { return position ; } 
    Vector3D get_position_above_surface() const { return (position-Vector3D {0,RADIUS_E,0}); }
    


    //setters
    void reduce_mass(double amount) {mass-=amount;}
    void update_position(Vector3D& velocity , double pace) {position+=velocity*pace;}
    void set_position(Vector3D& pos) {position=pos;}
};


