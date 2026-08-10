#include <mp-units/systems/si.h>


using namespace mp_units;
using namespace mp_units::si::unit_symbols; // not the best solition 

inline constexpr auto R_air = 287.05 * J / (kg * K);


class Atmosphere {
    //private:
    public:
    quantity<K> temperature;       
    quantity<Pa> pressure;           
    quantity<kg / m3> density() const {
        
        return pressure / (R_air * temperature);
    }
    //double speedOfSound;         // a, m/s





    //public:
};