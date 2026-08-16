#include "../../include/Enviroment/Atmosphere.h"

void Atmosphere::set_tempeture(quantity<m> geometric_altitude){
        quantity isa_boundary = delta<m>(84'852);
        quantity termpsphere_boundary = delta<m>(200'000);
        quantity exosprhehe_boundary = delta<m>(1'000'000); // not specifically
        if(geometric_altitude < 0 * m){
        throw std::domain_error("Negative geopotential altitude");
        }
        else if (geometric_altitude < isa_boundary){
        temperature = atmo_layer.compute_temperature(get_geopotential_altitude(geometric_altitude));
        }
        else if (geometric_altitude<termpsphere_boundary){
            std::cerr << "Not func termosphere";
        }
        else if (geometric_altitude<exosprhehe_boundary){
            std::cerr << "Not func exosphere";
        }
        else std::cerr << "Not correct function was used";
    };
