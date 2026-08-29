#include "../Enviroment/Atmosphere.h"
#include "../Rocket.h" 

class Flight_parameters
{

    public:

    VelocityVec get_real_velocity()const {return real_velocity;};
    quantity<one> get_mach_number()const {return mach_number; };
    quantity<one> get_reynolds_number() const {return reynolds_number;};
    quantity<Pa> get_dynamic_pressure() const {return dynamic_pressure;};
  

    Flight_parameters(Atmosphere& atm_r) : atm(atm_r) {};




    void set_real_velocity(Vector3D rocket_vel){
        VelocityVec rocket_speed = make_vec<isq::velocity, m / s>(rocket_vel.x,rocket_vel.y,rocket_vel.z);
        real_velocity = rocket_speed - atm.get_wind_vel();
    }
    void set_mach_number(){
        mach_number = magnitude(real_velocity) / atm.get_sonic_velocity();
    }

    void set_dynamic_pressure(){
        dynamic_pressure = 0.5 * atm.get_density() * mp_units::pow<2>(magnitude(real_velocity));
    }

    void set_reynolds_number(quantity<m> lenght) {
        reynolds_number = (atm.get_density() * magnitude(real_velocity) * lenght) / atm.get_viscosity();
    }





    private:
    const Atmosphere& atm;
    VelocityVec real_velocity;
    quantity<one> mach_number;
    quantity<one> reynolds_number;
    quantity<Pa> dynamic_pressure;



    

    
};





