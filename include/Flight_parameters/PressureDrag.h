#pragma once 
#include "../Utility/Constants.h"
#include <array>


class PressureDrag{
    public:

    quantity<one> get_DPressue(quantity<one>& mach){
        return CdNose+CdBase;
    }


    private:
    quantity<one> CdNose;
    quantity<one> CdBase;
    quantity<one> DPressure;

    //for Sref = 10.75 m2  / It's falcon9 only 
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
    }

}