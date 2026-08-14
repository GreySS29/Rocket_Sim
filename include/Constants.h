#pragma once
#include <mp-units/systems/si.h>

using namespace mp_units;
using namespace mp_units::si::unit_symbols; // not the best solition 

#include <math.h>
//Earth
constexpr double G = 6.674e-11; //gravity const: 6.674 × 10⁻¹¹ Н·m²/kg²
const double RADIUS_E = 6'371'000.0;//m

//Atmosphere
inline constexpr auto R_air                  = 287.05 * J / (kg * K);
inline constexpr auto troposphere_top        = 11'000 * m;
inline constexpr auto tropopause_top         = 20'000 * m;
inline constexpr auto lower_stratosphere_top = 32'000 * m;
inline constexpr auto stratosphere_top       = 47'000 * m;



