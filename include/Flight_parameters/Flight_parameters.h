#pragma once
#include "../Enviroment/Atmosphere.h"
#include "../Rocket.h" 
#include "Friction_drag.h"

class Flight_parameters
{

    public:

    VelocityVec get_real_velocity()const {return real_velocity;};
    quantity<one> get_mach_number()const {return mach_number; };
    quantity<Pa> get_dynamic_pressure() const {return dynamic_pressure;};
    quantity<one> get_reynolds_number() const {return reynolds_number;};
    quantity<N> get_friction_drag() const {return friction_drag;};
    

    Flight_parameters(const Atmosphere& atm_r) : atm(atm_r) {};

    void update_flight_par (Vector3D rocket_vel, quantity<m> length , quantity<kg/m3> density, quantity<m2> a_wet) {
        set_real_velocity(rocket_vel);
        set_mach_number();
        set_dynamic_pressure();
        set_reynolds_number(length);
        friction_drag = fdrag.calculate_friction_drag(reynolds_number,mach_number, density, mp_units::abs(magnitude(real_velocity)), a_wet);
        fdrag.check_2(reynolds_number,mach_number, density, mp_units::abs(magnitude(real_velocity)), a_wet);
    }


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

    

    
    

    void print_parameters (std::ofstream& ofs) const {
        ofs << "Vr :" << get_real_velocity() << '\t' 
        << "Mach :" << get_mach_number() << '\t'
        << "Q :" << get_dynamic_pressure() << '\t'
        << "R :" << get_reynolds_number() << '\t'
        << "Dfric :" << get_friction_drag() << '\n';
    }

    // void print_parameters () const  {
    //     skindrag.set_laminar_flow_fraction(reynolds_number);
    //     std::cout << skindrag.laminar_flow_fraction << '\n';
    // }




    private:
    VelocityVec real_velocity;
    quantity<one> mach_number;
    quantity<Pa> dynamic_pressure;
    quantity<one> reynolds_number;
    quantity<N> friction_drag;
    const Atmosphere& atm;
    Friction_drag fdrag;





    

    
};





