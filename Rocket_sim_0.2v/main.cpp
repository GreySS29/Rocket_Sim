#include "iostream"
#include "include/Gravity_temp.h"
#include "include/Earth.h"
#include "include/Tank.h"
#include "include/Engine.h"
#include "include/Stage.h"



int main() {
    Earth earth;
    // for (double i = 0; i < 100000.0; i+=10000.0)
    // {
    //     Engine engine {20000,100,earth.surfacePoint(i), 50};
    //     //Tank tank {earth.surfacePoint(i),20.0,0};
    //     double s = gravity_magnitude (earth, engine);
    //     std::cout << s << '\n';
    // }   
    Engine engine {20000,100,earth.surfacePoint(2), 50};
    Tank tank {earth.surfacePoint(10), 50,20};
    Stage stage {earth.surfacePoint(10000),&engine,&tank};
    std::cout<<stage.get_mass() << "\t" <<stage.get_position()<<'\n';
    std::cout<<gravity_magnitude(earth,stage);

} 