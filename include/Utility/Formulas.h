#include "Constants.h"


//common formulas without nose cone and fins 
// static quantity<m2> calculate_surface_area (const quantity<m>& length, const  quantity<m>& diameter)
// {
//     quantity<m2> A_side =  (mp_units::pi * diameter * length);
//     quantity<m2> A_caps = 2 * mp_units::pi * mp_units::pow<2>(diameter / 2);
//     return A_side + A_caps;
// }



static double calculate_surface_area (const double& length, const double&  diameter)
{
    double A_side = pi_double * diameter * length;
    double A_caps = 2 * pi_double * std::pow(diameter / 2, 2);
    return A_side + A_caps;
}

