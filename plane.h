#ifndef MODULE_SPATIAL_PLANE_H_
#define MODULE_SPATIAL_PLANE_H_

#include "vec.h"
#include "line.h"

namespace Spatial {

    class Plane {

        Vec<3> normal, point;
        float_max_t d;

    public:

        Plane (const Vec<3> &_normal, const Vec<3> &_point) :
            normal(_normal.normalized()), point(_point), d(_normal.dot(_point)) {}

        Plane(const Vec<3> &_normal, float_max_t _d);

        inline const Vec<3> &getNormal (void) const { return this->normal; }
        inline const Vec<3> &getPoint (void) const { return this->point; }

        inline float_max_t getA (void) const { return this->normal[0]; }
        inline float_max_t getB (void) const { return this->normal[0]; }
        inline float_max_t getC (void) const { return this->normal[0]; }
        inline float_max_t getD (void) const { return this->d; }

        inline bool inside (const Vec<3> &point) const { float_max_t result = this->normal.dot(point) - d; return closeToZero(result); }

        bool intersectLine(const Line &line, Vec<3> &normal, float_max_t &t_inter, bool fix_normal = true);

    };
};

#endif
