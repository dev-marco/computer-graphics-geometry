#include "../intersection.h"
#include "polyhedron.h"

namespace Spatial {

    bool Polyhedron::intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {

        unsigned face_min, face_max;
        const std::vector<Plane> &planes = this->getPlanes();

        if (Intersection::Line::Polyhedron(
            line.getPoint(), line.getDirection(),
            planes,
            t_min, face_min, t_max, face_max
        )) {
            if (fix_normals) {
                normal_min = planes[face_min].getNormal().opposed(line.getDirection());
                normal_max = planes[face_max].getNormal().opposed(line.getDirection());
            } else {
                normal_min = planes[face_min].getNormal();
                normal_max = planes[face_max].getNormal();
            }
            return true;
        }
        return false;
    }

};
