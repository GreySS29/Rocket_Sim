
#include "../Constants.h"
#include "../Earth.h"





class Atmosphere {
    private:
    quantity<m> get_geopotential_altitude (quantity<m> geometric_altitude)
        {
            return (Earth::mean_radius * geometric_altitude) / (Earth::mean_radius + geometric_altitude);
        }

    public:
    quantity<K> temperature;       
    quantity<Pa> pressure;           
    quantity<kg / m3> density() const {
        
        return pressure / (R_air * temperature);
    }
    
    //double speedOfSound;         // a, m/s
    

    void set_tempeture(quantity<m> geometric_altitude){
        quantity<m> geopot_al = get_geopotential_altitude(geometric_altitude);
        quantity<K> temp_b = delta<K>(288.15);
        quantity<K/m> temp_grad = -0.0065 * K/m;
        if (geopot_al < 0) {
            //expetion
            return;
        }
        else if (troposphere_top <= geopot_al && geopot_al < tropopause_top) // 20k - 32k
        {
            temp_grad = 0.001 * K/m;
            temperature = (216.65 * K) + temp_grad * (geopot_al - troposphere_top);

        }
        else if (troposphere_top <= geopot_al && geopot_al < tropopause_top) // 11k - 20k
        {
            temperature = 216.65 * K; // Tb ~ 11 km
        }
        else if (0 <= geopot_al && geopot_al < troposphere_top)
        {
            temperature = temp_b + temp_grad * geopot_al;
        }

    }



    //public:
};