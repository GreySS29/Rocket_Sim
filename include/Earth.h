#pragma once
#include "Physic_object.h"
#include <cmath>
#include <memory>
#include "Enviroment/Atmosphere.h"

//AccelerationVec gravity   = make_vec<isq::acceleration, m / s2>(0., -9.81, 0.);

class Earth : public Physic_object
{
 

    public:

    

    Earth () :Physic_object ({0,0,0}, 5.972E+24), atm_(std::make_unique<Atmosphere>()) {}

    

    Vector3D surfacePoint(double height_above_surface) const // for objects' construction 
    {
        return position + Vector3D{0,RADIUS_E+height_above_surface,0};
    };

    double get_air_density(double height) const; 
    
    Vector3D get_dragForce_vec(const auto* object) const
    {
        double density = get_air_density(object->get_position_above_surface().y);
        if (density <=0) return Vector3D(0,0,0);

        Vector3D v_vec = object->get_velocity();
        double v = v_vec.magnitude();

        if(v==0) {
            //std::cout<<"v=0";
            return Vector3D(0,0,0); 
            
        }
        double drag = 0.5 * density * v * v * object->get_C_D() * object->get_AREA();
        
        return v_vec.normalize() * (-drag);
    };

    void update (quantity<m> altitude) {atm_->update(altitude);};
    void get_status () const { atm_->get_status();};
    void print_atmo_status (std::ofstream& ofs,quantity<m> altitude) const { atm_ ->print_to_log(ofs,altitude);};
    const Atmosphere& get_Atmo_parameters() const { return *atm_;};

    const double get_orbital_velocity(double target) const
     { return std::sqrt(MU_EARTH / (RADIUS_E + target));};



    private:
    const double RADIUS_E = 6371000.0; //m
    const double ATMOSPHERE_HEIGHT = 100000.0;//m 
    const double AIR_DENSITY_SURFACE = 1.225; // kg/m3
    const double MU_EARTH = 3.986004418e14; // м^3/с^2
    std::unique_ptr<Atmosphere> atm_;
    
    inline static constexpr quantity<m> equatorial_radius =6'378'137 * m;
    inline static constexpr quantity<m> polar_radius =6'356'752.3 * m;



};