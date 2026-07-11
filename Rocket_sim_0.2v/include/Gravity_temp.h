#pragma once
#include "Constants.h"
#include "Vector3D.h"
#include <concepts>



template<typename T>
concept HasMass = requires(T a) {a.get_mass();};

template<typename T>
concept HasPosition = requires(T a) {a.get_position();};

template<typename A, typename B=A> //
requires HasMass<A> && HasMass<B> && HasPosition<A> && HasPosition<B>
double gravity_magnitude (const A& a, const B& b) // scalar ... H 
{
    double r = (a.get_position() - b.get_position()).magnitude();
    return G * (a.get_mass() *b.get_mass()) / (r*r);
}

template<typename A, typename B=A>
requires HasMass<A> && HasMass<B> && HasPosition<A> && HasPosition<B>
Vector3D gravity_vec(const A& a, const B& b) 
{
   
    return Vector3D(0, (-gravity_magnitude(a,b)), 0);
     
}



