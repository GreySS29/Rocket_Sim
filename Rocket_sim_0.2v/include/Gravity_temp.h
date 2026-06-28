#pragma once
#include "Constants.h"
#include "Vector3D.h"
#include <concepts>



template<typename T>
concept HasMass = requires(T a) {a.getMass();};

template<typename T>
concept HasPosition = requires(T a) {a.getPosition();};

template<typename A, typename B>
requires HasMass<A> && HasMass<B> && HasPosition<A> && HasPosition<B>
double gravity_magnitude (const A& a, const B& b) // 
{
    double r = (a.getPosition() - b.getPosition()).magnitude();
    return G * (a.getMass() *b.getMass()) / (r*r);
}

//vector gravity force