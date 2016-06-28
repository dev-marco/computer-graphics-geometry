#include "line.h"

namespace Geometry {

    float_max_t Line::param (const Vec<3> &point) const {

        const Vec<3>
            &line_point = this->getPoint(),
            &line_direction = this->getDirection();

        if (!closeToZero(line_direction[0])) {
            return (point[0] - line_point[0]) / line_direction[0];
        } else if (!closeToZero(line_direction[1])) {
            return (point[1] - line_point[1]) / line_direction[1];
        }

        return (point[2] - line_point[2]) / line_direction[2];

    }

};
