#include "../intersection.h"
#include "sphere.h"

namespace Geometry {

    Vec<2> Sphere::param (const Vec<3> &point) const {
        const Vec<3> diff = point - this->getCenter();
        return { std::acos(clamp(diff[2] / this->getRadius(), -1.0, 1.0)) / PI, std::atan2(diff[1], diff[0]) / TWO_PI };
    }

    bool Sphere::intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_t &t_min, float_t &t_max, bool fix_normals) const {
        if (Intersection::Line::Sphere(line.getPoint(), line.getDirection(), this->getCenter(), this->getRadius(), t_min, t_max)) {
            normal_min = (line.at(t_min) - this->getCenter()).normalized();
            normal_max = (line.at(t_max) - this->getCenter()).normalized();

            this->param(line.at(t_min));

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

};
