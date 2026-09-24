#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>
#include <mp-units/utility/cartesian_vector.h>

using Vec3 = mp_units::utility::cartesian_vector<double>;

template<auto QS, auto U>
using vec_quantity = quantity<QS[U], Vec3>;

template<auto QS, auto U>
constexpr auto make_vec(double x, double y, double z) {
    return QS(Vec3{x, y, z} * U);
}

using VelocityVec     = vec_quantity<isq::velocity, m / s>;
using AccelerationVec = vec_quantity<isq::acceleration, m / s2>;
using PositionVec     = vec_quantity<isq::position_vector, m>;