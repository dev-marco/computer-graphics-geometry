#include "../intersection.h"
#include "cylinder.h"

namespace Geometry {

    bool Cylinder::intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_t &t_min, float_t &t_max, bool fix_normals) const {

        bool is_t_min_top_cap, is_t_min_bottom_cap, is_t_max_top_cap, is_t_max_bottom_cap;

        if (Intersection::Line::Cylinder(
            line.getPoint(), line.getDirection(),
            this->getBottom(), this->getTop(), this->getRadius(),
            t_min, is_t_min_top_cap, is_t_min_bottom_cap,
            t_max, is_t_max_top_cap, is_t_max_bottom_cap
        )) {
            static Vec<3> direction, delta;
            direction = this->getDirection();

            if (is_t_min_top_cap) {
                normal_min = direction;
            } else if (is_t_min_bottom_cap) {
                normal_min = -direction;
            } else {
                delta = line.at(t_min) - this->getTop();
                normal_min = delta - delta.dot(direction) * direction;
            }

            if (is_t_max_top_cap) {
                normal_max = direction;
            } else if (is_t_max_bottom_cap) {
                normal_max = -direction;
            } else {
                delta = line.at(t_max) - this->getTop();
                normal_max = delta - delta.dot(direction) * direction;
            }

            if (fix_normals) {
                normal_min.oppose(line.getDirection());
                normal_max.oppose(line.getDirection());
            }

            return true;
        }
        return false;
    }

};
