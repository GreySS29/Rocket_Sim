#pragma once
#include <mp-units/systems/si.h>
#include <mp-units/math.h>

using namespace mp_units;
using namespace mp_units::si::unit_symbols; // not the best solition 



#include <math.h>
//Earth
constexpr double G = 6.674e-11; //gravity const: 6.674 × 10⁻¹¹ Н·m²/kg²
const double RADIUS_E = 6'371'000.0;//m
constexpr auto Standard_gravity = 9.80665 * m / pow<2>(s);

//Atmosphere
constexpr auto Sea_level_temperature  = delta<K>(288.15);
constexpr auto Sea_level_pressure = 101325 * Pa;
constexpr auto Dry_air_specific_gas_constant = 287.052 * pow<2>(m) / (pow<2>(s) * K);
constexpr auto Gaz_constant = 8.314462 * J / (mol*K);



//for testing
constexpr auto eps_T = delta<K> (0.01);   
constexpr auto eps_P = 0.5 * Pa;   
constexpr auto eps_rho = 1e-4 * (kg/m3);
constexpr auto eps_v = 0.01 * (m/s);






