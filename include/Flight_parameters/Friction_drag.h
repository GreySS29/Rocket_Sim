#pragma once
#include "../Constants.h"
#include <cmath>
#include <array>


class Friction_drag {
   

    static constexpr quantity<one> сritical_Reynolds_number {5e+5};
    static constexpr quantity<one> unity{1};
    static constexpr quantity<one> Laminar_num{1.328};
    static constexpr quantity<one> Turbulent_num{0.074};
    // static constexpr quantity<one> unity{1};
    // static constexpr quantity<one> unity{1};
    quantity<one> prop_coeff;                       // Proportionality coefficient
    quantity<one> Ft_M;                             // Turbulent compressibility correction factor
    quantity<one> Fl_M; 	                        // Laminar compressibility correction factor
    quantity<one> skin_friction_coefficient;
    static constexpr std::array< std::pair <quantity<one>, quantity<one>>, 7 > tbl_Fl_M {
        {{0. , 0.0391}, {0.7 , 0.0392} , {1. , 0.0381} , {1.5 , 0.0371} , {2.0 , 0.0329} , {2.5 , 0.0286} , {3.0 , 0.0261}}
    };
    

    public:
    
    void set_prop_coeff(const quantity<one> reynolds_number){
        prop_coeff = 
        std::min(сritical_Reynolds_number/reynolds_number , unity);
    }

    //Blasius formula, polynomial correction 
    void set_Fl_M(const quantity<one> n_mach){ 
    
        Fl_M =1 - (0.689 * n_mach) - (0.0343 * mp_units::pow<2>(n_mach)) 
        + (0.0061 * mp_units::pow<3>(n_mach)) - (0.000278 * mp_units::pow<4>(n_mach)); 
    }

    void set_Ft_M(const quantity<one> n_mach){ // temporary decision 
        for(size_t i =1; i < tbl_Fl_M.size(); ++i){
            if (n_mach<tbl_Fl_M[i].first) {
                quantity<one> t = (n_mach - tbl_Fl_M[i-1].first) / (tbl_Fl_M[i].first-tbl_Fl_M[i-1].first);
                quantity<one> F = tbl_Fl_M[i-1].second + t * (tbl_Fl_M[i].second - tbl_Fl_M[i-1].second);
                Ft_M = F / tbl_Fl_M[0].second;
                return;
            }
        }
        Ft_M = tbl_Fl_M.back().second / tbl_Fl_M[0].second;
        
    }

    void set_skin_friction_coefficient(){

    }

    quantity<one> get_prop_coeff() const {return prop_coeff;};
    quantity<one> get_Fl_M() const {return Fl_M;};
    quantity<one> get_Ft_M() const {return Ft_M;};


};