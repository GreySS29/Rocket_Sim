#pragma once
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

// quantity<one> aero_scale(quantity<si::metre> h)
// {
//     constexpr double h0 = 80e3, h1 = 100e3;
//     const double x = h.numerical_value_in(si::metre);
//     if (x <= h0) return 1.0 * one;
//     if (x >= h1) return 0.0 * one;
//     return (1.0 - (x - h0) / (h1 - h0)) * one;
// }

static quantity<one> aero_scale(const double h)
{
    constexpr double h0 = 80e3, h1 = 100e3;
    if (h <= h0) return 1.0 * one;
    if (h >= h1) return 0.0 * one;
    return (1.0 - (h - h0) / (h1 - h0)) * one;
}
