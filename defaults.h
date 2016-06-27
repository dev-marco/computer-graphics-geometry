#ifndef MODULE_GRAPHICS_GEOMETRY_DEFAULTS_H_
#define MODULE_GRAPHICS_GEOMETRY_DEFAULTS_H_

#include <iostream>
#include <cmath>

typedef double float_max_t;

namespace Geometry {

    constexpr float_max_t
        EPSILON = 1e-10,
        PI = 3.141592653589793238462643383279502884,
        TWO_PI = PI + PI,
        DEG15 = PI / 12.0,
        DEG30 = PI / 6.0,
        DEG45 = PI / 4.0,
        DEG60 = PI / 3.0,
        DEG90 = PI / 2.0,
        DEG135 = DEG90 + DEG45,
        DEG180 = PI,
        DEG225 = -DEG135,
        DEG270 = -DEG90,
        DEG315 = -DEG45,
        DEG360 = 0.0,
        DEG2RAD = DEG180 / 180.0,
        RAD2DEG = 180.0 / DEG180;

    template <typename T>
    constexpr T clamp (const T &value, const T &min_value, const T &max_value) {
        if (value > max_value) {
            return max_value;
        } else if (value < min_value) {
            return min_value;
        }
        return value;
    }

    constexpr float_max_t fract (const float_max_t &value) { return value - std::floor(value); }

    constexpr bool closeTo (const float_max_t &value, const float_max_t &close, const float_max_t &much = EPSILON) { return (close - much) <= value && value <= (close + much); }
    constexpr bool closeToZero (const float_max_t &value, const float_max_t &much = EPSILON) { return -much <= value && value <= much; }
};

#endif
