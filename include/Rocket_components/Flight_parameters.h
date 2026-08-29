#include "../Enviroment/Atmosphere.h"
#include "../Rocket.h" 

class Flight_parameters
{

    public:

    VelocityVec get_real_velocity(){return real_velocity;};




    void set_real_velocity(Vector3D rocket_vel,Atmosphere& atm){
        VelocityVec rocket_speed = make_vec<isq::velocity, m / s>(rocket_vel.x,rocket_vel.y,rocket_vel.z);
        real_velocity = rocket_vel - atm.get_wind_vel();
    }
    // void set_mach_nubmer(quantity<m/s>& sonic_velocity){
    //     mach_number = real_velocity / sonic_velocity;
    // }



    private:
    VelocityVec real_velocity;
    // quantity<one> mach_number;

    

    
};





