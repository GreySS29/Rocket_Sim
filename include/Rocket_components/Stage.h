#pragma once 
#include "../Physic_object.h"
#include "Engine.h"
#include "Payload.h"
#include "Tank.h"
#include "../Earth.h"
#include "../Gravity_temp.h"







class Stage : public Physic_object {
    private:
    //std::vector<std::unique_ptr<T> for plenty Engines and tanks
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Tank> tank;
    Vector3D velocity; //m.s
    Vector3D acceleration; //m/s2
    quantity<m> length;
    quantity<m2> a_wet;  //Wetted area

    public:
    Stage (Vector3D position,double c_d, double area, std::unique_ptr<Engine> eng, std::unique_ptr<Tank> t , quantity<m> len , quantity<m2> area_wet) :
        Physic_object{position, eng->get_mass() + t->get_mass(), c_d, area}, 
        engine(std::move(eng)),
        tank(std::move(t)), // give this object to Stage
        length(len),
        a_wet(area_wet)
        {
            velocity = Vector3D(0,0,0);
            acceleration = Vector3D(0,0,0);
            
        };

        
    

    //getters
    Vector3D get_velocity() const {return velocity;}
    Vector3D get_acceleration() const {return acceleration;}
    double get_thrust() const {return engine->get_thrust();}
    double get_fuel_mass() const { return tank -> get_fuel_mass();}
    Vector3D get_thrust_direction() const {return engine->get_thrust_direction();}
    quantity<m> get_length() const {return length;};
    quantity<m2> get_a_wet() const {return a_wet;};


    //setters
    void set_velocity(double pace) { velocity+=acceleration * pace;}
    void set_acceleration(Vector3D& f_total, double mass) {acceleration= f_total/mass;
    }
    void set_direction(double angle) {engine->set_thrust_direction(angle);}
    
    void move_parameters (const Stage& booster){
        velocity = booster.get_velocity();
        position = booster.get_position();

    }
    


    static std::unique_ptr<Stage> creat_stage(double position_h,double c_d , double area, Engine&, Tank&, const Earth& earth, quantity<m> lenght, quantity<m2> area_wet);
    void launch_stage(const Earth&, double pace);  
    Vector3D run_engine(bool command);
    


    //print
    void print_status_flight() const;
    void print_status() const;
    void print_status_flight_short() const;
   
};