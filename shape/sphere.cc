#include "../intersection.h"
#include "sphere.h"

namespace Spatial {

    bool Sphere::intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {
        if (Intersection::Line::Sphere(line.getPoint(), line.getDirection(), this->getCenter(), this->getRadius(), t_min, t_max)) {
            normal_min = (line.at(t_min) - this->getCenter()).normalized();
            normal_max = (line.at(t_max) - this->getCenter()).normalized();

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

};
