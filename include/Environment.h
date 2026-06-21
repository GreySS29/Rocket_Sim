#pragma once
#include "Vector3D.h"
#include "Rocket.h"
const double GRAVITY = 9.81;//m/c2
const double EARTH_RADIUS = 6371000.0;//m
const double ATMOSPHERE_HEIGHT = 100000.0;//m 
const double AIR_DENSITY_SURFACE = 1.225; // kg/m3
const double TARGET_HEIGHT = 200000.0; //m


//DragForce
const double C_D = 0.3; //Коэффициент сопротивления
const double AREA = 10.0; //Area


const double PACE = 0.1; // pace


const double V_ORBITAL = std::sqrt(GRAVITY * ((EARTH_RADIUS*EARTH_RADIUS)/(EARTH_RADIUS+TARGET_HEIGHT)));

class Enviroment {
    public:
    double getAirDensity(double height) const ; // // Плотность воздуха на высоте (экспоненциальная модель)
    Vector3D getGravityForce(const Rocket& rocket) const;
    Vector3D getDragForce(const Rocket& rocket) const;
    void step(Rocket& rocket); // Шаг симуляции (метод Эйлера)
};

