#pragma once
#include "Vector3D.cpp"

class RocketState {
    public:
    Vector3D position;  //m
    Vector3D velocity; // m/s
    Vector3D acceleration; // m/s2
    double mass; //kg
    double fuel; //kg
    double time;

    RocketState(double mass =50000, double fuel = 40000) : mass(mass), fuel(fuel) , time(0){
        position = Vector3D(0,0,0);
        velocity = Vector3D(0,0,0);
        acceleration = Vector3D(0,0,0);
    }
};