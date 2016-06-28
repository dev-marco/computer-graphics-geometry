#ifndef MODULE_GEOMETRY_PARAMETRIC_H_
#define MODULE_GEOMETRY_PARAMETRIC_H_

#include <tuple>
#include <unordered_map>
#include "defaults.h"
#include "vec.h"
#include "quaternion.h"
#include "plane.h"

namespace Geometry {

    namespace Parametric {

        inline Vec<2> Plane (
            const Plane &plane,
            const Vec<3> &point
        ) { return plane.param(point); }

        Vec<2> Cylinder (
            const Vec<3> &cylinder_bottom,
            const Vec<3> &cylinder_direction,
            const float_max_t &cylinder_height,
            const float_max_t &cylinder_radius,
            const Vec<3> &point
        );

        Vec<2> Sphere (
            const Vec<3> &sphere_center,
            const float_max_t &sphere_radius,
            const Vec<3> &point
        );
    };
};

#endif
