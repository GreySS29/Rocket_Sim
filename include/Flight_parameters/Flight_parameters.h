#pragma once
#include "../Enviroment/Atmosphere.h"
#include "../Rocket.h" 

#include "FrictionDrag.h"
#include "PressureDrag.h"

class Flight_parameters
{

    public:

    VelocityVec get_real_velocity()const {return real_velocity_;};
    quantity<one> get_mach_number()const {return mach_number_; };
    quantity<Pa> get_dynamic_pressure() const {return dynamic_pressure_;};
    quantity<one> get_reynolds_number() const {return reynolds_number_;};
    quantity<one> get_friction_drag() const {return friction_drag_;};
    quantity<one> get_pressure_drag() const {return pressure_drag_;}


    //last force
    //quantity<one> cd_total = pressure.get_dPressure() + friction.get_friction_drag();
    //quantity<si::newton> drag = cd_total * 0.5 * density * velocity * velocity * stage->get_sRef();

    Flight_parameters(const Atmosphere& atm_r) : atm_(atm_r) {};

    void update_flight_par (Vector3D rocket_vel, quantity<m> length , quantity<kg/m3> density, 
        quantity<m2> a_wet, const Stage* stage) {

        set_real_velocity(rocket_vel);
        set_mach_number();
        set_dynamic_pressure();
        set_reynolds_number(length);
        friction_drag_ = fdrag_.calculate_friction_drag(reynolds_number_,mach_number_, stage, a_wet);
        // fdrag.check_2(reynolds_number,mach_number, density, mp_units::abs(magnitude(real_velocity)), a_wet);
        pressure_drag_ = pdrag_.calculate_pressure_drag(mach_number_, stage);

    }


    void set_real_velocity(Vector3D rocket_vel){
        VelocityVec rocket_speed = make_vec<isq::velocity, m / s>(rocket_vel.x,rocket_vel.y,rocket_vel.z);
        real_velocity_ = rocket_speed - atm_.get_wind_vel();
    }
    void set_mach_number(){
        mach_number_ = magnitude(real_velocity_) / atm_.get_sonic_velocity();
    }

    void set_dynamic_pressure(){
        dynamic_pressure_ = 0.5 * atm_.get_density() * mp_units::pow<2>(magnitude(real_velocity_));
    }

    void set_reynolds_number(quantity<m> lenght) {
        reynolds_number_ = (atm_.get_density() * magnitude(real_velocity_) * lenght) / atm_.get_viscosity();
    }

    
    void print_parameters (std::ofstream& ofs) const {
        ofs << "Vr :" << get_real_velocity() << '\t' 
        << "Mach :" << get_mach_number() << '\t'
        << "Q :" << get_dynamic_pressure() << '\t'
        << "R :" << get_reynolds_number() << '\t'
        << "Dfric :" << get_friction_drag() << '\t'
        << "Dpress :" << get_pressure_drag() << '\n';
    }

    // void print_parameters () const  {
    //     skindrag.set_laminar_flow_fraction(reynolds_number);
    //     std::cout << skindrag.laminar_flow_fraction << '\n';
    
    // }




    private:
    VelocityVec real_velocity_;
    quantity<one> mach_number_;
    quantity<Pa> dynamic_pressure_;
    quantity<one> reynolds_number_;
    quantity<one> friction_drag_;
    quantity<one> pressure_drag_;
    const Atmosphere& atm_;
    FrictionDrag fdrag_;
    PressureDrag pdrag_;





   

    
};





