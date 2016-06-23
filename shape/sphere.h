#ifndef MODULE_SPATIAL_SPHERE_H_
#define MODULE_SPATIAL_SPHERE_H_

#include "shape.h"

namespace Spatial {

    class Sphere : public Shape {

        Vec<3> center;
        float_max_t radius;

    public:
        Sphere (const Vec<3> &_center, float_max_t _radius) :
            center(_center), radius(_radius) {}

        inline const Vec<3> &getCenter (void) const { return this->center; }
        inline float_max_t getRadius (void) const { return this->radius; }

        inline void setCenter (const Vec<3> &_center) { this->center = _center; }
        inline void setRadius (const Vec<3> &_radius) { this->radius = _radius; }

        inline bool fit (void) const override { return true; }

        inline const Shape *boundingVolume (void) const override { return this; }

        const char *getType (void) const override { return "sphere"; };

        inline Shape *clone (void) const override { return new Sphere(this->getCenter(), this->getRadius()); }

        bool intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals = true) const override;

    };

}

#endif
