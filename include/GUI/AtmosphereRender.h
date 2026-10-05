#pragma once 

#include "../Enviroment/Atmosphere.h"
#include "../Utility/Constants.h"

class AtmosphereRender {

    public:
    quantity<K> temperature;
    quantity<Pa> pressure;
    quantity<kg / m3> density;

    void set_temperature (const quantity<K>& temp) {temperature = temp;}
    void set_pressure (const quantity<Pa>& pres) {pressure = pres;}
    void set_density (const quantity<kg/m3>& dens) {density = dens;}


};