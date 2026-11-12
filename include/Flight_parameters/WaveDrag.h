#pragma once 
#include "../Utility/Constants.h"


class WaveDrag{
    public:
    constexpr quantity<one> M_cr = 0.75 * one; //claude
    constexpr quantity<one> M_dd = 0.86 * one; //claude
    constexpr quantity<one> M_pic = 1.1 * one; //claude
    constexpr quantity<one> C_pic = 0.25 * one; //claude
    quantity<one> C_w;
    quantity<one> C_dd; // ~ 0205 
    quantity<one> s;

    consteval void set_C_dd (){
                                                                //C_dd = 0,12 * C_pic;
                                                                //k = C_dd / (M_dd − M_кр)⁴
        C_dd = 205 * mp_units::pow<4>(M_dd - M_cr);
    }

    void set_s (const quantity<one>&  M) {
        s = (M - M_dd) / (M-pic - M_dd);
    }

    void set_C_w (const quantity<one>& M) {

        if (M <=M_cr) C_w = 0 * one; // 1 

        if (M <=M_dd) C_w = k * mp_units::pow<4>(M - M_cr); //2 C_Dw = k · (M − M_кр)⁴

        if (M <= M_pic) C_w = C_dd + (C_pic - C_dd) * ((3* mp_units::pow<2>(s))-(2*mp_units::pow<3>(s))); // alternative ~ m_dd = 4k(M_dd − M_кр)³

        if (M > M_pic) C_w = A / mp_units::sqrt(mp_units::pow<2>(M) - 1);





    }

    
}
