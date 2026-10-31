#pragma once 
#include "../Utility/Constants.h"
#include <array>


class PressureDrag{
    public:

    quantity<one> get_DPressue() const{
        return dPressure_;
    };

    quantity<one> get_cdNose() const {
        return cdNose_;
    }

    quantity<one> get_cdBase() const {
        return cdBase_;
    }

    quantity<one> calculate_pressure_drag(const quantity<one>& mach, const Stage* stage){
        set_CdBase(mach);
        set_CdNose(mach);
        set_dPressure(stage);
        return get_DPressue();
    }

    void check(const Stage* stage) {
        PressureDrag prd;
        // for 14 km falcon 9
        const quantity<one> mach = 0.5;
        prd.calculate_pressure_drag(mach, stage);
        std::cout << "C__base : " << prd.get_cdBase() << '\n'
        << "C_base_eff : " << prd.get_Cdbase_eff(stage) << '\n'
        << "C__nose : " << prd.get_cdNose() << '\n'
        << "D__pres : " <<prd.get_DPressue() << '\n';
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

        }   };

    void set_dPressure(const Stage* stage){

        dPressure_=cdNose_+get_Cdbase_eff(stage);
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

    //effective base square. depend on status of engines // only falcon (9 merlin) 
    quantity<one> get_Cdbase_eff(const Stage* stage)
    {
        const quantity<m2> Seff =
            (stage->empty_tank() ? 0.8 : 0.2) * stage->get_sRef();

        return get_cdBase() * (Seff / stage->get_sRef());
    }



    

};