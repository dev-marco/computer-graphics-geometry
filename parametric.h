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


        inline Vec<2> Cylinder (
            const Vec<3> &cylinder_bottom,
            const Vec<3> &cylinder_direction,
            const float_max_t &cylinder_height,
            const Vec<3> &point
        ) {
            const Vec<3> diff = Quaternion::difference(Vec<3>::axisZ, cylinder_direction).rotated(point - cylinder_bottom);
            return { std::atan2(diff[1], diff[0]) / TWO_PI, diff[2] / cylinder_height };
        }

        inline Vec<2> Sphere (
            const Vec<3> &sphere_center,
            const float_max_t &sphere_radius,
            const Vec<3> &point
        ) {
            const Vec<3> diff = point - sphere_center;
            return { std::acos(clamp(diff[2] / sphere_radius, -1.0, 1.0)) / PI, std::atan2(diff[1], diff[0]) / TWO_PI };
        }

        inline Vec<2> Plane (
            const Plane &plane,
            const Vec<3> &point
        ) { return plane.param(point); }

    };

};

#endif
