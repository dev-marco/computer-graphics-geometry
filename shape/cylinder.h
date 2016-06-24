#ifndef MODULE_GRAPHICS_GEOMETRY_CYLINDER_H_
#define MODULE_GRAPHICS_GEOMETRY_CYLINDER_H_

#include "shape.h"

namespace Geometry {

    class Cylinder : public Shape {

        Vec<3> bottom, top, direction;
        float_max_t radius, height;

        inline void updateDirection (void) { Vec<3> diff = this->getTop() - this->getBottom(); this->height = diff.length(); this->direction = diff.resized(this->height, 1.0); }

    public:

        Cylinder (const Vec<3> &_bottom, const Vec<3> &_top, float_max_t _radius) :
            bottom(_bottom), top(_top), radius(_radius) { this->updateDirection(); }

        inline const Vec<3> &getBottom (void) const { return this->bottom; }
        inline const Vec<3> &getTop (void) const { return this->top; }
        inline const Vec<3> &getDirection (void) const { return this->direction; }
        inline float_max_t getRadius (void) const { return this->radius; }
        inline float_max_t getHeight (void) const { return this->height; }

        inline void setBottom (const Vec<3> &_bottom) { this->bottom = _bottom; this->updateDirection(); }
        inline void setTop (const Vec<3> &_top) { this->top = _top; this->updateDirection(); }
        inline void setRadius (float_max_t _radius) { this->radius = _radius; }

        inline bool fit (void) const override { return true; }

        inline const Shape *boundingVolume (void) const override { return this; }

        const char *getType (void) const override { return "cylinder"; };

        inline Shape *clone (void) const override { return new Cylinder(this->getBottom(), this->getTop(), this->getRadius()); }

        Vec<2> param(const Vec<3> &point) const;

        bool intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals = true) const override;

    };
};

#endif
