#ifndef MODULE_SPATIAL_BOX_H_
#define MODULE_SPATIAL_BOX_H_

#include "../defaults.h"
#include "../vec.h"
#include "../line.h"
#include "shape.h"

namespace Spatial {

    class Box : public Shape {

        Vec<3> min, max;

        public:

            Box (const Vec<3> &_min, const Vec<3> &_max) :
                min(_min), max(_max) {}

            inline const Vec<3> &getMin (void) const { return this->min; }
            inline const Vec<3> &getMax (void) const { return this->max; }

            inline void setMin (const Vec<3> &_min) { this->min = _min; }
            inline void setMax (const Vec<3> &_max) { this->max = _max; }

            inline const Shape *boundingVolume (void) const override { return this; }

            const char *getType (void) const override { return "box"; }

            inline Shape *clone (void) const override { return new Box(this->getMin(), this->getMax()); }

            inline bool fit (void) const override { return true; }

            bool intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals = true) const override;

    };
};

#endif
