#pragma once
#include "../Constants.h"
#include <array>

class Friction_drag {
   

   

    public:

    quantity<N> calculate_friction_drag(const quantity<one>& reynolds_number,const quantity<one>& n_mach, 
        const quantity<kg/m3>& density, const quantity<m/s>& velocity, const quantity<m2>& a_wet){

        set_prop_coeff(reynolds_number);
        set_Fl_M(n_mach);
        set_Ft_M(n_mach);
        set_skin_friction_coefficient(reynolds_number);
        set_friction_drag(density,velocity,a_wet);
        return get_friction_drag();
    }
    



    void check () {
        Friction_drag frd;
        //for 14 km falcon 9 
        const quantity<one> reyn = 591480423.51;
        const quantity<one> mach = 1.75;
        const quantity<kg/m3> density = 0.23 * kg/m3;
        const quantity<m/s> velocity = 516.07 * m/s;
        const quantity<m2> a_wet = 846 * m2;
        frd.set_prop_coeff(reyn);
        frd.set_Fl_M(mach);
        frd.set_Ft_M(mach);
        frd.set_skin_friction_coefficient(reyn);
        frd.set_friction_drag(density,velocity,a_wet);
        std::cout<<frd.get_prop_coeff()<<'\n'
        << "Fl_M :" << frd.get_Fl_M() <<'\n'
        << "Ft_M :" << frd.get_Ft_M() <<'\n'
        << "skin coef : " << frd.get_skin_friction_coefficient() << '\n'
        << "friction_drag : " << frd.get_friction_drag() << '\n';
        
    }

    void check_2(const quantity<one>& reynolds_number,const quantity<one>& n_mach,quantity<kg / m3> density, quantity<m/s> velocity, quantity<m2> a_wet) {
        set_prop_coeff(reynolds_number);
        set_Fl_M(n_mach);
        set_Ft_M(n_mach);
        set_skin_friction_coefficient(reynolds_number);
        set_friction_drag(density,velocity,a_wet);
        std::cout<<"proportion :" <<get_prop_coeff()<<'\n'
        << "Fl_M :" << get_Fl_M() <<'\n';
        // << "Ft_M :" << get_Ft_M() <<'\n'
        // << "skin coef : " << get_skin_friction_coefficient() << '\n'
        // << "friction_drag : " << get_friction_drag() << '\n';

    }


    private:

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
    quantity<N> friction_drag;


    static constexpr std::array< std::pair <quantity<one>, quantity<one>>, 7 > tbl_Fl_M { 
        {{0. , 0.0391}, {0.7 , 0.0392} , {1. , 0.0381} , {1.5 , 0.0371} , {2.0 , 0.0329} , {2.5 , 0.0286} , {3.0 , 0.0261}}
    };
    

    void set_prop_coeff(const quantity<one>& reynolds_number){
        prop_coeff = std::min(сritical_Reynolds_number/reynolds_number , unity);
    }

    //Blasius formula, polynomial correction 
    void set_Fl_M(const quantity<one>& n_mach){ 
        Fl_M = mp_units::abs(1 - (0.689 * n_mach) - (0.0343 * mp_units::pow<2>(n_mach)) + (0.0061 * mp_units::pow<3>(n_mach)) - (0.000278 * mp_units::pow<4>(n_mach))); 
    }

    void set_Ft_M(const quantity<one>& n_mach){ // temporary decision with interpolation 
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

    void set_skin_friction_coefficient(const quantity<one>& reynolds_number){
        quantity <one> laminar_part = prop_coeff * (1.328 / mp_units::sqrt(сritical_Reynolds_number)) + (1 - prop_coeff);
        quantity<one> turbulent_part = (0.074 / mp_units::pow<1, 5>(reynolds_number)) - (0.074 / mp_units::pow<1, 5>(сritical_Reynolds_number));  
        skin_friction_coefficient = laminar_part * Fl_M * Ft_M * turbulent_part;
    }

     void set_friction_drag(quantity<kg / m3> density, quantity<m/s> velocity, quantity<m2> a_wet)
     {
        friction_drag = 0.5 * density * velocity * velocity * skin_friction_coefficient * a_wet;
     }


     quantity<one> get_prop_coeff() const {return prop_coeff;};
    quantity<one> get_Fl_M() const {return Fl_M;};
    quantity<one> get_Ft_M() const {return Ft_M;};
    quantity<one> get_skin_friction_coefficient() const {return skin_friction_coefficient;};
    quantity<N> get_friction_drag() const {return friction_drag;};

};