#ifndef MODULE_GRAPHICS_GEOMETRY_SHAPE_H_
#define MODULE_GRAPHICS_GEOMETRY_SHAPE_H_

#include "../defaults.h"
#include "../vec.h"
#include "../line.h"

namespace Geometry {

    class Shape {

    public:

        constexpr Shape (void) {}
        virtual ~Shape (void) {}

        virtual bool fit (void) const = 0;

        virtual const Shape *boundingVolume (void) const = 0;

        virtual const char *getType (void) const = 0;

        virtual Shape *clone (void) const = 0;

        virtual bool intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const = 0;

    };
}

#endif
