#include "../../include/Enviroment/Atmosphere.h"

void Atmosphere::set_tempeture(quantity<m> geometric_altitude){
        quantity isa_boundary = delta<m>(86'000);
        quantity termpsphere_boundary = delta<m>(500'000); // temporary
        quantity exosprhehe_boundary = delta<m>(1'000'000); // not specifically
        if(geometric_altitude < 0 * m){
        throw std::domain_error("Negative geopotential altitude");
        }
        else if (geometric_altitude <= isa_boundary){
        temperature = layer_isa.compute_temperature(get_geopotential_altitude(geometric_altitude));
        //pressure = layer_isa.compute_pressure();

        }
        else if (geometric_altitude<=termpsphere_boundary){
            temperature = layer_termosphere.get_temp_termo(geometric_altitude);
        }
        else if (geometric_altitude<exosprhehe_boundary){
            std::cerr << "Not func exosphere";
        }
        else std::cerr << "Not correct function was used";
    };
