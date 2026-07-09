#pragma once 
#include "Physic_object.h"
#include "Engine.h"
#include "Tank.h"
#include "Earth.h"
#include "Templates.h"
#include <memory>



class Stage : public Physic_object {
    private:
    //std::vector<std::unique_ptr<T> for plenty Engines and tanks
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Tank> tank;
    Vector3D velocity; //m.s
    Vector3D acceleration; //m/s2

    public:
    Stage (Vector3D position, std::unique_ptr<Engine> eng, std::unique_ptr<Tank> t) :
        Physic_object{position, eng->get_mass() + t->get_mass()}, 
        engine(std::move(eng)),
        tank(std::move(t)) // give this object to Stage
        {
            velocity = Vector3D(0,0,0);
            acceleration = Vector3D(0,5,0);
            
        };

        
    static std::unique_ptr<Stage> creat_stage(Engine&, Tank&, Earth& earth);

    //getters
    Vector3D get_velocity() const {return velocity;};
    Vector3D get_acceleration() const {return acceleration;}



    //setters
    void set_velocity(double pace) { velocity+=acceleration * pace;}
};