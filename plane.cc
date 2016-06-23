#include "plane.h"
#include "intersection.h"

namespace Spatial {

    Plane::Plane (const Vec<3> &_normal, float_max_t _d) :
        normal(_normal.normalized()), d(_d) {
        if (this->normal[0] != 0.0) {
            point = { -d / this->normal[0], 0.0, 0.0 };
        } else if (this->normal[1] != 0.0) {
            point = { 0.0, -d / this->normal[1], 0.0 };
        } else {
            point = { 0.0, 0.0, -d / this->normal[2] };
        }
    }

    bool Plane::intersectLine (const Line &line, Vec<3> &normal, float_max_t &t_inter, bool fix_normal) {
        if (Intersection::Line::Plane(line.getPoint(), line.getDirection(), *this, t_inter)) {
            if (fix_normal) {
                normal = this->getNormal().opposed(line.getDirection());
            } else {
                normal = this->getNormal();
            }
            return true;
        }
        return false;
    }

};
