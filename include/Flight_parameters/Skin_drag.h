#pragma once
#include "../Constants.h"
#include <cmath>


class Skin_drag {
   

    static constexpr quantity<one> сritical_Reynolds_number {5e+5};
    static constexpr quantity<one> unity{1};
    static constexpr quantity<one> Laminar_num{1.328};
    static constexpr quantity<one> Turbulent_num{0.074};
    // static constexpr quantity<one> unity{1};
    // static constexpr quantity<one> unity{1};
    quantity<one> prop_coeff;            // Proportionality coefficient
    quantity<one> Ft_M;                             // Turbulent compressibility correction factor
    quantity<one> Fl_M; 	                        // Laminar compressibility correction factor
    quantity<one> skin_friction_coefficient;
    

    public:
    
    void set_prop_coeff(const quantity<one> reynolds_number){
        laminar_flow_fraction = 
        std::min(сritical_Reynolds_number/reynolds_number , unity);
    }

    void set_skin_friction_coefficient(){

    }

    quantity<one> get_prop_coeff() const {return prop_coeff;};


};