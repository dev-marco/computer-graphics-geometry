#ifndef MODULE_SPATIAL_DEFAULTS_H_
#define MODULE_SPATIAL_DEFAULTS_H_

typedef double float_max_t;

namespace Spatial {

    static constexpr float_max_t
        EPSILON = 0.0000000000000001L,
        PI = 3.141592653589793238462643383279502884L,
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
        DEG360 = PI + PI;

    template <typename T>
    inline static constexpr T clamp (const T value, const T min_value, const T max_value) {
        if (value > max_value) {
            return max_value;
        } else if (value < min_value) {
            return min_value;
        }
        return value;
    }
};

#endif
