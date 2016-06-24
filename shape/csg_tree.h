#ifndef MODULE_GRAPHICS_GEOMETRY_CSG_TREE_H_
#define MODULE_GRAPHICS_GEOMETRY_CSG_TREE_H_

#include "shape.h"

namespace Geometry {

    class CSGTree : public Shape {

    public:

        enum Type {
            UNION,
            INTERSECTION,
            SUBTRACTION
        };

    private:

        Shape *first, *second;
        Type operation;

    public:

        constexpr CSGTree (Shape *_first, Type _operation, Shape *_second) :
            first(_first), second(_second), operation(_operation) {}

        inline Shape *getFirst (void) const { return this->first; }
        inline Shape *getSecond (void) const { return this->second; }
        inline Type getOperation (void) const { return this->operation; }

        inline bool fit (void) const override { return true; }

        inline const Shape *boundingVolume (void) const override { return this; }

        inline const char *getType (void) const override { return "csg_tree"; }

        inline Shape *clone (void) const override { return new CSGTree(this->getFirst(), this->getOperation(), this->getSecond()); }

        bool intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_t &t_min, float_t &t_max, bool fix_normals) const override;

    };

};

#endif
