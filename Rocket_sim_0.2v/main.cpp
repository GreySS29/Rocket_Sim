#include "iostream"
#include "include/Gravity_temp.h"
#include "include/Earth.h"
#include "include/Tank.h"




int main() {
    Earth earth;
    for (double i = 0; i < 100000.0; i+=10000.0)
    {
        Tank tank {earth.surfacePoint(i),20.0,0};
        double s = gravity_magnitude (earth, tank);
        std::cout << s << '\n';
    }   
}