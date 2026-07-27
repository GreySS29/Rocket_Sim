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
    void set_velocity(double pace) { velocity_+=acceleration_ * pace;}
    void set_acceleration(Vector3D& f_total) {acceleration_= f_total/get_mass();}; 
    void update_mass(){
        if (booster_!= nullptr){
            mass = booster_->get_mass()+upper_stage_->get_mass()+payload_.get_mass();
        }
        else mass = upper_stage_->get_mass()+payload_.get_mass();
    }
    void update_condition(double pace){
        update_mass();
        // set_acceleration();
        set_velocity(pace);
        update_position(velocity_,pace);
    }

    Stage active(){
        return booster_ != nullptr ? booster_ : upper_stage_;
    }
    
    
    void launch_booster (const Earth& earth, double pace);
    void run_upper_stage (const Earth& earth, double pace);

    std::unique_ptr<Stage> separate_booster(){
        std::unique_ptr<Stage> booster = std::move(booster_);
        booster_ = nullptr;
        update_mass();
        upper_stage_->set_direction(70);
        return booster;
    }


    void set_direction(double angle , int number) { //temporary
        if(number ==1) booster_->set_direction(angle);
        else if(number == 2) upper_stage_->set_direction(angle);
    }



   static std::unique_ptr<Rocket> create_rocket(std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload& payload, Earth& earth);
   void print_status() const;
   void print_status_flight() const;
   void print_status_flight_short() const;


   //command
   void run_engine(bool command, int stage) {
        switch (stage)
        {
        case 1:
            if(command == true) {booster_->run_engine(true);}
            else booster_->run_engine(false);
            break;

        case 2:
            if(command == true) {upper_stage_->run_engine(true);}
            else upper_stage_->run_engine(false);
            break;
        
        default:
            break;
        }
   }

};