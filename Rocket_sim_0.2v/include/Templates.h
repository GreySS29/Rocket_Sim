// #pragma once
// #include "Gravity_temp.h"
// #include <vector.h>

// template<typename C>
// concept HasMass = requires(C a) {
//     for (auto x : a){
//         a -> getMass();
//     }
//     };


// template<typename C>
// requires HasMass<C>  
// double sum_mass (const C& a) // 
// {
//     double sum_mass {};
//     for (auto x : a)
//     {
//         sum_mass+=x->getMass();
//     }
//     return sum_mass;
// }

