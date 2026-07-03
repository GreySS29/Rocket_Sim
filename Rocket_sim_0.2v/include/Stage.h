#pragma once 
#include "Physic_object.h"
#include "Engine.h"
#include "Tank.h"
#include "Templates.h"

class Stage : public Physic_object {
    private:
    Engine* engine;
    Tank* tank;

    public:
    Stage (Vector3D position, Engine* eng, Tank* t) :
        Physic_object{position, eng->get_mass() + t->get_mass()}, 
        engine(eng),
        tank(t)
        {};
    
};