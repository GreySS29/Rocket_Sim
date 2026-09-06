#pragma once
#include "Rocket_components/Stage.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include "GUI/RocketRender.h"
#include "Flight_parameters/Flight_parameters.h"

class Rocket  {
    private:
    std::unique_ptr<Stage> booster_;
    std::unique_ptr<Stage> upper_stage_;
    Payload payload_;
    Flight_parameters flight_p_;


    
    
    public:
    Rocket (std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload payload,const Atmosphere& atm_r ) :
    
         booster_(std::move(booster)),
         upper_stage_(std::move(upper_stage)),
         payload_(payload),
         flight_p_{atm_r}
         {
         };

    Stage* active() const {
    if (booster_) return booster_.get();
    if (upper_stage_) return upper_stage_.get();
    return nullptr;
    }

     //getters
    double get_mass() const {
    if (booster_)
        return booster_->get_mass() + upper_stage_->get_mass() + payload_.get_mass();
    return upper_stage_->get_mass() + payload_.get_mass();
    }

    quantity<m2> get_a_wet() const {
    if(booster_)
        return booster_->get_a_wet() + upper_stage_->get_a_wet() + payload_.get_a_wet();
    return upper_stage_->get_a_wet() + payload_.get_a_wet();
    }


    quantity<m> get_length() const {
        if (booster_)
            return booster_->get_length() + upper_stage_->get_length();
        return upper_stage_->get_length();
    }


    Vector3D get_velocity() const {return active()->get_velocity();};
    Vector3D get_acceleration() const {return  active()->get_acceleration();}
    Vector3D get_position() const {return active()->get_position();}
    Vector3D get_position_above_face() const {return active()->get_position_above_surface();}
    
    void run (const Earth& earth, double pace,RocketRender& roc_render);
 

    std::unique_ptr<Stage> separate_booster(){
        upper_stage_->move_parameters(*booster_);
        std::unique_ptr<Stage> booster = std::move(booster_);
        booster_ = nullptr;
        return booster;
    }

    void set_direction(double angle) { active()->set_direction(angle);};
    Vector3D get_direction() const { return active() ->get_thrust_direction();} 


   static std::unique_ptr<Rocket> create_rocket(std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload payload, const Earth& earth);
   void print_status() const;
   void print_status_flight() const;
   void print_status_flight_short() const;
   void print_status_flight_short(std::ofstream& ofs, int time) const;
};

