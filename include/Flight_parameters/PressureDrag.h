#pragma once 
#include "../Utility/Constants.h"
#include <array>


class PressureDrag{
    public:

    quantity<one> get_DPressue(){
        return dPressure_;
    };

    quantity<one> get_cdNose() const {
        return cdNose_;
    }

    quantity<one> get_cdBase() const {
        return cdBase_;
    }

    quantity<one> calculate_pressure_drag(const quantity<one>& mach){
        set_CdBase(mach);
        set_CdNose(mach);
        set_dPressure();
        return get_DPressue();
    }

    private:
    quantity<one> cdNose_;
    quantity<one> cdBase_;
    quantity<one> dPressure_;

    //for Sref = 10.75 m2  / It's falcon9 only 
    //linear interpolation from a table / mach - coef
    static constexpr std::array<std::pair <quantity<one>, quantity<one>> , 11>  tbl_Cd_nose_Falcon9 {
        {
            {0.0 , 0.035},
            {0.6 , 0.035},
            {0.8 , 0.040},
            {0.9 , 0.070},
            {1.0 , 0.130},
            {1.1 , 0.160},
            {1.2 , 0.150},
            {1.5 , 0.120},
            {2.0 , 0.100},
            {3.0 , 0.085},
            {5.0 , 0.075},

        }
    };

    void set_dPressure(){

        dPressure_=cdNose_+cdBase_;
    }

    //0.12 + 0.13M^2 , M<1 || 0.25/M, M>1
    void set_CdBase (const quantity<one>& mach) {
        if (mach<1 * one) cdBase_ =  0.12 + (0.13 * mach *mach);
        else cdBase_ = 0.25/mach ; 
    };

    void set_CdNose(const quantity<one>& mach) {
        const auto& t = tbl_Cd_nose_Falcon9;

        if (mach <= t.front().first) { 
            cdNose_ = t.front().second; 
            return; }
        if (mach >= t.back().first)  { 
            cdNose_ = t.back().second;  
            return; }

        for (std::size_t i = 1; i < t.size(); ++i) {
            if (mach <= t[i].first) {
                const auto& [m0, c0] = t[i - 1];
                const auto& [m1, c1] = t[i];
                cdNose_ = c0 + (c1 - c0) * ((mach - m0) / (m1 - m0));
                return;
            }
        }
    }

    

};