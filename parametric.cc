#include "parametric.h"

namespace Geometry {

    namespace Parametric {

        Vec<2> Cylinder (
            const Vec<3> &cylinder_bottom,
            const Vec<3> &cylinder_direction,
            const float_max_t &cylinder_height,
            const float_max_t &cylinder_radius,
            const Vec<3> &point
        ) {
            const Vec<3> diff = Quaternion::difference(cylinder_direction, Vec<3>::axisZ).rotated(point - cylinder_bottom);
            if (diff[2] > EPSILON && diff[2] < (cylinder_height - EPSILON))  {
                return { std::atan2(diff[1], diff[0]) * cylinder_radius, diff[2] };
            } else {
                return { std::atan2(diff[1], diff[0]) * cylinder_radius, 0.0 };
            }
        }

        Vec<2> Sphere (
            const Vec<3> &sphere_center,
            const float_max_t &sphere_radius,
            const Vec<3> &point
        ) {
            const Vec<3> diff = point - sphere_center;
            return { std::acos(clamp(diff[2] / sphere_radius, -1.0, 1.0)) * sphere_radius, std::atan2(diff[1], diff[0]) * sphere_radius };
        }
    };
};
