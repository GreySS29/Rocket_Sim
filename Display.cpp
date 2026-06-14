#include "Display.h"
#include "Rocket.h"


void Display::printStatus(const Rocket& rocket) {
    
    RocketState& state = rocket.getState();
    std::cout << std::fixed << std::setprecision(2);
        std::cout << "=== Состояние ракеты ===\n";
        std::cout << "Время: " << state.time << " с\n";
        std::cout << "Высота: " << state.position.y << " м (" << state.position.y/1000 << " км)\n";
        std::cout << "Скорость: " << state.velocity.magnitude() << " м/с (" << state.velocity.magnitude()/3600 << " км/ч)\n";
        std::cout << "Ускорение: " << state.acceleration.magnitude() << " м/с² (" << state.acceleration.magnitude()/GRAVITY << " g)\n";
        std::cout << "Масса: " << state.mass << " кг\n";
        std::cout << "Топливо: " << state.fuel << " кг\n";
        std::cout << "=========================\n";
};