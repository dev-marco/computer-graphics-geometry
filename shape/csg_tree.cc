#include "csg_tree.h"

namespace Spatial {

    bool CSGTree::intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {
        unsigned min_index, max_index;
        Vec<3> shapes_normal[4];
        float_max_t shapes_inter[4];
        bool shapes_result[2], global_result = false;
        shapes_result[0] = this->getFirst()->intersectLine(line, shapes_normal[0], shapes_normal[2], shapes_inter[0], shapes_inter[2], fix_normals);
        if (shapes_result[0] || this->getOperation() != Type::SUBTRACTION) {
            shapes_result[1] = this->getSecond()->intersectLine(line, shapes_normal[1], shapes_normal[3], shapes_inter[1], shapes_inter[3], fix_normals);
            if (shapes_result[0]) {
                if (shapes_result[1]) {
                    switch (this->getOperation()) {
                        case Type::UNION:
                            min_index = shapes_inter[0] < shapes_inter[1] ? 0 : 1;
                            max_index = shapes_inter[2] > shapes_inter[3] ? 2 : 3;
                            global_result = true;
                        break;
                        case Type::INTERSECTION:
                            min_index = shapes_inter[0] < shapes_inter[1] ? 1 : 0;
                            max_index = shapes_inter[2] > shapes_inter[3] ? 3 : 2;
                            global_result = shapes_inter[min_index] <= shapes_inter[max_index];
                        break;
                        case Type::SUBTRACTION:
                            if (shapes_inter[0] < shapes_inter[1]) {
                                min_index = 0;
                                max_index = shapes_inter[2] < shapes_inter[1] ? 2 : 1;
                                global_result = true;
                            } else if (shapes_inter[3] < shapes_inter[2]) {
                                if (shapes_inter[0] > shapes_inter[3]) {
                                    min_index = 0;
                                    max_index = 2;
                                } else {
                                    min_index = 3;
                                    max_index = 2;
                                }
                                global_result = true;
                            }
                    }
                } else if (this->getOperation() != Type::INTERSECTION) {
                    min_index = 0;
                    max_index = 2;
                    global_result = true;
                }
            } else if (shapes_result[1] && this->getOperation() == Type::UNION) {
                min_index = 1;
                max_index = 3;
                global_result = true;
            }
        }
        if (global_result) {
            t_min = shapes_inter[min_index];
            t_max = shapes_inter[max_index];
            normal_min = shapes_normal[min_index];
            normal_max = shapes_normal[max_index];
        }
        return global_result;
    }

};
