#include "Stage.h"
#include "Payload.h"



class Rocket  {
    private:
    std::unique_ptr<Stage> booster_;
    std::unique_ptr<Stage> upper_stage_;
    Payload& payload_;
    


    public:
    Rocket (std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload& payload ) :
    
         booster_(std::move(booster)),
         upper_stage_(std::move(upper_stage)),
         payload_(payload)
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

    Vector3D get_velocity() const {return active()->get_velocity();};
    Vector3D get_acceleration() const {return  active()->get_acceleration();}
    Vector3D get_position() const {return active()->get_position();}
    //Vector3D get_position_above_surface  () const {return active()->get_position_above_surface();}

    //setters
   
   // void set_acceleration(Vector3D& f_total) {acceleration_= f_total/get_mass();}; //!!! 
    

    
    void run (const Earth& earth, double pace);
    // void launch_booster (const Earth& earth, double pace);
    // void run_upper_stage (const Earth& earth, double pace);

    std::unique_ptr<Stage> separate_booster(){
        upper_stage_->move_parameters(*booster_);
        std::unique_ptr<Stage> booster = std::move(booster_);
        booster_ = nullptr;
        return booster;
    }


    // void set_direction(double angle , int number) { //temporary
    //     if(number ==1) booster_->set_direction(angle);
    //     else if(number == 2) upper_stage_->set_direction(angle);
    // }



   static std::unique_ptr<Rocket> create_rocket(std::unique_ptr<Stage> booster, std::unique_ptr<Stage> upper_stage, Payload& payload, Earth& earth);
   void print_status() const;
   void print_status_flight() const;
   void print_status_flight_short() const;


//    //command
//    void run_engine(bool command, int stage) {
//         switch (stage)
//         {
//         case 1:
//             if(command == true) {booster_->run_engine(true);}
//             else booster_->run_engine(false);
//             break;

//         case 2:
//             if(command == true) {upper_stage_->run_engine(true);}
//             else upper_stage_->run_engine(false);
//             break;
        
//         default:
//             break;
//         }
//    }

};