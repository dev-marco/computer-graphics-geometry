#include "intersection.h"

namespace Spatial {

    namespace Intersection {

        namespace Point {

            bool Point (
                const Vec<3> &point_1,
                const Vec<3> &point_2,
                Vec<3> &closest_point
            ) {
                closest_point = point_1;
                return point_1.distance2(point_2) <= EPSILON;
            }

            bool Line (
                const Vec<3> &point,
                const Vec<3> &line_point,
                const Vec<3> &line_delta,
                Vec<3> &intersection_point,
                float_max_t &t_inter
            ) {
                Vec<3> near_point;
                const float_max_t length_2 = line_delta.length2();
                float_max_t param = 0.0;

                if (length_2 == 0.0) {
                    near_point = line_point;
                } else {
                    param = ((point - line_point) * line_delta).sum() / length_2;
                    near_point = line_point + (param * line_delta);
                }

                t_inter = param;

                const bool result = near_point.distance2(point) <= EPSILON;
                intersection_point.swap(near_point);
                return result;
            }

            bool Plane (
                const Vec<3> &point,
                const Vec<3> &plane_normal,
                const Vec<3> &plane_point,
                Vec<3> &intersection_point
            ) {
                Vec<3> near_point = point + plane_normal * ((plane_normal.dot(plane_point) - plane_normal.dot(point)) / plane_normal.length2());
                const bool result = near_point.distance2(point) <= EPSILON;
                intersection_point.swap(near_point);
                return result;
            }
        };

        namespace Line {

            bool Line (
                const Vec<3> &line_1_point,
                const Vec<3> &line_1_delta,
                const Vec<3> &line_2_point,
                const Vec<3> &line_2_delta,
                float_max_t &t_1,
                float_max_t &t_2
            ) {
                const Vec<3> rays_delta = line_1_point - line_2_point;

                const float_max_t
                    line_1_size2 = line_1_delta.length2(),
                    line_2_size2 = line_2_delta.length2();

                float_max_t mu_a = 0.0, mu_b = 0.0;

                if (line_1_size2 <= EPSILON) {
                    if (line_2_size2 > EPSILON) {
                        mu_b = clamp(line_2_delta.dot(rays_delta) / line_2_size2, 0.0, 1.0);
                    }
                } else {
                    const float_max_t c = line_1_delta.dot(rays_delta);

                    if (line_2_size2 <= EPSILON) {
                        mu_a = clamp(-c / line_1_size2, 0.0, 1.0);
                    } else {
                        const float_max_t
                            b = line_1_delta.dot(line_2_delta),
                            denom = line_1_size2 * line_2_size2 - b * b,
                            f = line_2_delta.dot(rays_delta);

                        if (denom != 0.0) {
                            mu_a = clamp((b * f - c * line_2_size2) / denom, 0.0, 1.0);
                        }

                        const float_max_t numer = b * mu_a + f;

                        if (numer <= 0.0) {
                            mu_a = clamp(-c / line_1_size2, 0.0, 1.0);
                        } else if (numer >= line_2_size2) {
                            mu_b = 1.0;
                            mu_a = clamp((b - c) / line_1_size2, 0.0, 1.0);
                        } else {
                            mu_b = numer / line_2_size2;
                        }
                    }
                }

                t_1 = mu_a, t_2 = mu_b;

                return true;
            }

            bool Plane (
                const Vec<3> &line_point,
                const Vec<3> &line_delta,
                const Vec<3> &plane_normal,
                const Vec<3> &plane_d,
                float_max_t &t_inter
            ) {
                const float_max_t dot = plane_normal.dot(line_delta);
                if (dot >= EPSILON || dot <= -EPSILON) {
                    t_inter = (plane_d - plane_normal.dot(line_point)) / dot;
                    return true;
                }
                return false;
            }

            bool Sphere (
                const Vec<3> &line_point,
                const Vec<3> &line_delta,
                const Vec<3> &sphere_center,
                const float_max_t &sphere_radius,
                float_max_t &t_min,
                float_max_t &t_max
            ) {
                const float_max_t line_length_inv = 1.0 / line_delta.length();
                const Vec<3> diff = line_point - sphere_center;
                const float_max_t
                    b = diff.dot(line_delta * line_length_inv),
                    c = diff.length2() - sphere_radius * sphere_radius;

                if (c > 0.0 && b > 0.0) {
                    return false;
                }

                const float_max_t discr = (b * b) - c;

                if (discr < 0.0) {
                    return false;
                }

                const float_max_t
                    sqrt_discr = std::sqrt(discr),
                    mu_1 = -(b + sqrt_discr) * line_length_inv,
                    mu_2 = (sqrt_discr - b) * line_length_inv;

                if (mu_1 > mu_2) {
                    t_min = mu_2, t_max = mu_1;
                } else {
                    t_min = mu_1, t_max = mu_2;
                }

                return true;
            }

            bool Box (
                const Vec<3> &line_point,
                const Vec<3> &line_delta,
                const Vec<3> &box_min,
                const Vec<3> &box_max,
                float_max_t &t_min,
                float_max_t &t_max
            ) {
                float_max_t
                    mu_min = -std::numeric_limits<float_max_t>::infinity(),
                    mu_max = std::numeric_limits<float_max_t>::infinity();

                for (unsigned i = 0; i < 3; ++i) {
                    if (std::abs(line_delta[i]) < Spatial::EPSILON) {
                        if (line_point[i] < box_min[i] || line_point[i] > box_max[i]) {
                            return 0;
                        }
                    } else {
                        float_max_t
                            ood = 1.0 / line_delta[i],
                            t1 = (box_min[i] - line_point[i]) * ood,
                            t2 = (box_max[i] - line_point[i]) * ood;
                        if (t1 > t2) {
                            std::swap(t1, t2);
                        }
                        if (t1 > mu_min) {
                            mu_min = t1;
                        }
                        if (t2 < mu_max) {
                            mu_max = t2;
                        }
                        if (mu_min > mu_max) {
                            return false;
                        }
                    }
                }

                t_min = mu_min, t_max = mu_max;
                return true;
            }

            bool Cylinder (
                const Vec<3> &line_point,
                const Vec<3> &line_delta,
                const Vec<3> &cylinder_bottom,
                const Vec<3> &cylinder_top,
                const float_max_t &cylinder_radius,
                float_max_t &t_min,
                float_max_t &t_max,
                bool &is_cap_min,
                bool &is_cap_max
            ) {
                const Vec<3>
                    cylinder_delta = cylinder_top - cylinder_bottom,
                    diff = line_point - cylinder_bottom;

                const float_max_t
                    md = diff.dot(cylinder_delta),
                    nd = line_delta.dot(cylinder_delta),
                    dd = cylinder_delta.length2(),
                    mdnd = md + nd;

                if (md < 0.0 && mdnd < 0.0) {
                    return false;
                } else if (md > dd && mdnd > dd) {
                    return false;
                }

                const float_max_t
                    nn = line_delta.dot(line_delta),
                    mn = diff.dot(line_delta),
                    a = dd * nn - nd * nd,
                    k = diff.length2() - cylinder_radius * cylinder_radius,
                    c = dd * k - md * md;

                float_max_t mu_1, mu_2;
                bool
                    intersect = false,
                    is_cap_mu_1 = false,
                    is_cap_mu_2 = false;

                if (a <= EPSILON && a >= -EPSILON) {
                    intersect = true;
                    if (c > 0.0) {
                        return false;
                    }
                    mu_1 = -mn / nn;
                    mu_2 = (nd - mn) / nn;
                    is_cap_mu_1 = is_cap_mu_2 = true;
                } else {
                    const float_max_t
                        b = dd * mn - nd * md,
                        discr = b * b - a * c;

                    if (discr < 0.0) {
                        return false;
                    }

                    const float_max_t
                        sqrt_discr = std::sqrt(discr),
                        a_inv = 1.0 / a;

                    mu_1 = -(b + sqrt_discr) * a_inv, mu_2 = (sqrt_discr - b) * a_inv;

                    if (md + (mu_1 * nd) < 0.0) {
                        is_cap_mu_1 = true;
                        mu_1 = -md / nd;
                        intersect = (k + mu_1 * (2.0 * mn + mu_1 * nn) <= 0.0);
                    } else if (md + (mu_1 * nd) > dd) {
                        is_cap_mu_1 = true;
                        mu_1 = (dd - md) / nd;
                        intersect = (k + dd - 2.0 * md + mu_1 * (2.0 * (mn - nd) + mu_1 * nn) <= 0.0);
                    } else {
                        intersect = true;
                    }

                    if (intersect) {
                        if (md + (mu_2 * nd) < 0.0) {
                            is_cap_mu_2 = true;
                            mu_2 = -md / nd;
                        } else if (md + (mu_2 * nd) > dd) {
                            is_cap_mu_2 = true;
                            mu_2 = (dd - md) / nd;
                        }
                    }
                }

                if (mu_1 > mu_2) {
                    is_cap_min = is_cap_mu_2, is_cap_max = is_cap_mu_1;
                    t_min = mu_2, t_max = mu_1;
                } else {
                    is_cap_min = is_cap_mu_1, is_cap_max = is_cap_mu_2;
                    t_min = mu_1, t_max = mu_2;
                }

                return intersect;
            }

            bool Polyhedron (
                const Vec<3> &line_point,
                const Vec<3> &line_delta,
                const std::vector<std::pair<Vec<3>, Vec<3>>> &planes,
                float_max_t &t_min,
                float_max_t &t_max,
                unsigned &face_min,
                unsigned &face_max
            ) {
                float_max_t
                    mu_min = -std::numeric_limits<float_max_t>::infinity(),
                    mu_max = std::numeric_limits<float_max_t>::infinity();
                Vec<3> plane_normal, plane_d;

                for (unsigned i = 0, size = planes.size(); i < size; ++i) {

                    std::tie(plane_normal, plane_d) = planes[i];

                    const float_max_t
                        denom = plane_normal.dot(line_delta),
                        dist = plane_d - plane_normal.dot(line_point);

                    if (denom <= EPSILON && denom >= -EPSILON) {
                        if (dist > 0.0) {
                            return false;
                        }
                    } else {
                        const float_max_t t = dist / denom;
                        if (denom < 0.0) {
                            if (t > mu_min) {
                                face_min = i;
                                mu_min = t;
                            }
                        } else if (t < mu_max) {
                            face_max = i;
                            mu_max = t;
                        }

                        if (mu_min > mu_max) {
                            return false;
                        }
                    }
                }

                t_min = mu_min, t_max = mu_max;

                return true;
            }
        };
    };
};
