#include "plane.h"
#include "intersection.h"

namespace Geometry {

    void Plane::calcForX (void) {
        float_max_t norm = -1.0 / this->normal[0];
        this->point = { this->getD() * norm, 0.0, 0.0 };
        this->s_param = { this->normal[1] * norm, 1.0, 0.0 };
        this->t_param = { this->normal[2] * norm, 0.0, 1.0 };
        this->s_index = 1, this->t_index = 2;
    }

    void Plane::calcForY (void) {
        float_max_t norm = -1.0 / this->normal[1];
        this->point = { 0.0, this->getD() * norm, 0.0 };
        this->s_param = { 1.0, this->normal[0] * norm, 0.0 };
        this->t_param = { 0.0, this->normal[2] * norm, 1.0 };
        this->s_index = 0, this->t_index = 2;
    }

    void Plane::calcForZ (void) {
        float_max_t norm = -1.0 / this->normal[2];
        this->point = { 0.0, 0.0, this->getD() * norm };
        this->s_param = { 1.0, 0.0, this->normal[0] * norm };
        this->t_param = { 0.0, 1.0, this->normal[1] * norm };
        this->s_index = 0, this->t_index = 1;
    }

    Plane::Plane (const Vec<3> &_normal, float_max_t _d) :
        normal(_normal.normalized()), d(_d) {
        float_max_t
            absx = std::abs(this->normal[0]),
            absy = std::abs(this->normal[1]),
            absz = std::abs(this->normal[2]);

        if (!closeToZero(absx) && absx < absy && absx < absz) {
            this->calcForX();
        } else if (!closeToZero(absy) && absy < absz) {
            this->calcForY();
        } else {
            this->calcForZ();
        }
    }

    bool Plane::param (const Vec<3> &point, float_max_t &s, float_max_t &t, bool in) {
        if (in || this->inside(point)) {
            s = point[this->s_index];
            t = point[this->t_index];
            return true;
        }
        return false;
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
