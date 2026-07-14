#include "Stage.h"
#include "Physic_object.h"
#include "Payload.h"



class Rocket : public Physic_object {
    private:
    std::unique_ptr<Stage> booster_;
    std::unique_ptr<Stage> upper_stage_;
    Payload& payload_;
    Vector3D velocity_;
    Vector3D acceleration_;


    public:
    Rocket (Vector3D position,double c_d, double area, 
        std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload& payload ) :
    Physic_object{position,
         booster->get_mass()+upper_stage->get_mass()+payload.get_mass(), c_d,area},
         booster_(std::move(booster)),
         upper_stage_(std::move(upper_stage)),
         payload_(payload)
         {
            velocity_ = Vector3D(0,0,0);
            acceleration_ = Vector3D (0,0,0);
         };

    
     //getters
    Vector3D get_velocity() const {return velocity_;};
    Vector3D get_acceleration() const {return acceleration_;}

    //setters
    void set_velocity(double pace) { velocity+=acceleration * pace;}
    void set_acceleration(Vector3D& f_total) {acceleration= f_total/this->get_mass();}; 
    
    
    void rocker_launch (const Earth&, double pace);
         



   static std::unique_ptr<Rocket> create_rocket(std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload& payload, Earth& earth);
   void print_status() const;

};