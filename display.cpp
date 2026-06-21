#include "Display.h"
#include "Rocket.h"
#include "Environment.h"
#include "Vector3D.h"
#include <iomanip>


void Display::printStatus(const Rocket& rocket) {
    
    const RocketState& state = rocket.getState();
    std::cout << std::fixed << std::setprecision(2);
        std::cout << "=== Состояние ракеты ===\n";
        std::cout << "Время: " << state.time << " с (" << state.time/60 << "m)\n";
        std::cout << "Высота: " << state.position.y << " м( " << state.position.y/1000 << " км)\n";
        std::cout << "Скорость: " << state.velocity.magnitude() << " м/с (" << state.velocity.magnitude()*3.6 << " км/ч)\n";
        std::cout << "Ускорение: " << state.acceleration.magnitude() << " м/с² (" << state.acceleration.magnitude()/GRAVITY << " g)\n";
        std::cout << "Масса: " << state.mass << " кг\n";
        std::cout << "Топливо: " << state.fuel << " кг\n";
        std::cout << "Направление : "<<rocket.getThustDirection() << '\n';
        std::cout << "=========================\n";
};