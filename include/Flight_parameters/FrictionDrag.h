#pragma once
#include "../Utility/Constants.h"
#include <array>
#include <iostream>
#include "../Rocket_components/Stage.h"

class FrictionDrag {
    public:

    quantity<one> calculate_friction_drag(const quantity<one>& reynolds_number,
        const quantity<one>& n_mach, 
        const Stage* stage,
        const quantity<m2>& a_wet);
    
    //for testing 
    // void check () ;
    // void check_2(const quantity<one>& reynolds_number,
    //     const quantity<one>& n_mach,
    //     const Stage& stage,
    //     const quantity<m2> a_wet); 

    private:

    static constexpr quantity<one> сritical_Reynolds_number {5e+5};
    static constexpr quantity<one> unity{1};
    static constexpr quantity<one> Laminar_num{1.328};
    static constexpr quantity<one> Turbulent_num{0.074};
    quantity<one> prop_coeff;                       // Proportionality coefficient
    quantity<one> Ft_M;                             // Turbulent compressibility correction factor
    quantity<one> Fl_M; 	                        // Laminar compressibility correction factor
    quantity<one> skin_friction_coefficient;
    quantity<one> friction_drag;

    static constexpr std::array< std::pair <quantity<one>, quantity<one>>, 7 > tbl_Fl_M { 
        {{0. , 0.0391}, 
        {0.7 , 0.0392}, 
        {1. , 0.0381} , 
        {1.5 , 0.0371}, 
        {2.0 , 0.0329}, 
        {2.5 , 0.0286}, 
        {3.0 , 0.0261}}
    };
    
    void set_prop_coeff(const quantity<one>& reynolds_number);
    void set_Fl_M(const quantity<one>& n_mach);     //Blasius formula, polynomial correction 
    void set_Ft_M(const quantity<one>& n_mach);     // temporary decision with interpolation 
    void set_skin_friction_coefficient(const quantity<one>& reynolds_number);
    void set_friction_drag(const Stage* stage, quantity<m2> a_wet);


    quantity<one> get_prop_coeff() const {return prop_coeff;};
    quantity<one> get_Fl_M() const {return Fl_M;};
    quantity<one> get_Ft_M() const {return Ft_M;};
    quantity<one> get_skin_friction_coefficient() const {return skin_friction_coefficient;};
    quantity<one> get_friction_drag() const {return friction_drag;};

};