#ifndef MODULE_GRAPHICS_GEOMETRY_PLANE_H_
#define MODULE_GRAPHICS_GEOMETRY_PLANE_H_

#include "vec.h"
#include "line.h"

namespace Geometry {

    class Plane {

        unsigned s_index, t_index;
        Vec<3> normal, point, s_param, t_param;
        float_max_t d;

        void calcForX (void);
        void calcForY (void);
        void calcForZ (void);

        void calcParams (void);

    public:

        Plane (const Vec<3> &_normal = Vec<3>::axisZ, const Vec<3> &_point = Vec<3>::origin) :
            normal(_normal.normalized()), point(_point), d(_normal.dot(_point)) { this->calcParams(); }

        Plane (const Vec<3> &_normal, float_max_t _d) :
            normal(_normal.normalized()), d(_d) { this->calcParams(); }

        inline const Vec<3> &getNormal (void) const { return this->normal; }
        inline const Vec<3> &getPoint (void) const { return this->point; }

        inline float_max_t getA (void) const { return this->normal[0]; }
        inline float_max_t getB (void) const { return this->normal[0]; }
        inline float_max_t getC (void) const { return this->normal[0]; }
        inline float_max_t getD (void) const { return this->d; }

        inline Vec<3> at (float_max_t s, float_max_t t) const { return this->getPoint() + s_param * s + t_param * t; }
        inline Vec<2> param (const Vec<3> &point) const { return { point[this->s_index], point[this->t_index] }; };

        inline bool inside (const Vec<3> &point) const { float_max_t result = this->normal.dot(point) - d; return closeToZero(result); }

        bool intersectLine(const Line &line, Vec<3> &normal, float_max_t &t_inter, bool fix_normal = true) const;

    };
};

#endif
