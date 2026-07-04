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

    public:
    Stage (Vector3D position, std::unique_ptr<Engine> eng, std::unique_ptr<Tank> t) :
        Physic_object{position, eng->get_mass() + t->get_mass()}, 
        engine(std::move(eng)),
        tank(std::move(t)) // give this object to Stage
        {};
    static std::unique_ptr<Stage> creat_stage(Engine&, Tank&, Earth& earth);
};