#pragma once 
#include "Physic_object.h"
#include "Engine.h"
#include "Tank.h"
#include "Earth.h"
#include "Templates.h"
#include <memory>
#include "Gravity_temp.h"
#include "Payload.h"




class Stage : public Physic_object {
    private:
    //std::vector<std::unique_ptr<T> for plenty Engines and tanks
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Tank> tank;
    Vector3D velocity; //m.s
    Vector3D acceleration; //m/s2

    public:
    Stage (Vector3D position,double c_d, double area, std::unique_ptr<Engine> eng, std::unique_ptr<Tank> t) :
        Physic_object{position, eng->get_mass() + t->get_mass(), c_d, area}, 
        engine(std::move(eng)),
        tank(std::move(t)) // give this object to Stage
        {
            velocity = Vector3D(0,0,0);
            acceleration = Vector3D(0,0,0);
            
        };

        
    

    //getters
    Vector3D get_velocity() const {return velocity;};
    Vector3D get_acceleration() const {return acceleration;}
    // Vector3D get_thrust_force();
    double get_thrust() const {return engine->get_thrust();}
    double get_fuel_mass() const { return tank -> get_fuel_mass();}


    //setters
    void set_velocity(double pace) { velocity+=acceleration * pace;}
    void set_acceleration(Vector3D& f_total) {acceleration= f_total/get_mass();
    }
    void set_direction(double angle) {engine->set_thrust_direction(angle);}
    
    


    static std::unique_ptr<Stage> creat_stage(double position_h, Engine&, Tank&, Earth& earth);
    void launch_stage(const Earth&, double pace);  
    Vector3D run_engine(bool command);
    


    //print
    void print_status_flight() const;
    void print_status() const;
    void print_status_flight_short() const;
   
};