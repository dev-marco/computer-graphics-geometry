#ifndef MODULE_GEOMETRY_POISSON_DISC_H_
#define MODULE_GEOMETRY_POISSON_DISC_H_

// Based on: https://bl.ocks.org/mbostock/dbb02448b0f93e4c82c3
// Also: http://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf

#include <random>
#include <chrono>
#include "defaults.h"
#include "vec.h"

namespace Geometry {

    class PoissonDisc {

        static std::mt19937 random_generator;

        const float_max_t radius, two_radius, radius2, width, height, cell_size, inv_cell_size;
        const unsigned samples, grid_width, grid_height;
        std::vector<Vec<2>> points;
        std::vector<int> queue;
        std::vector<std::vector<int>> grid;

        // This came from an ideia I had
        // After benchmarking, I found out this is usually 10x faster than the default sin(random_angle), cos(random_angle)
        static void randomSinCos (float_max_t &random_sin, float_max_t &random_cos);

        bool validPoint (const Vec<2> &point);
        void addPoint (const Vec<2> &point);

    public:

        PoissonDisc (const float_max_t &_radius, const float_max_t &_width = 1.0, const float_max_t &_height = 1.0, const unsigned &_samples = 10) :
            radius(_radius), two_radius(_radius + _radius), radius2(_radius * _radius),
            width(_width), height(_height),
            cell_size(_radius * SQRT_2_INV), inv_cell_size(1.0 / cell_size),
            samples(_samples),
            grid_width(std::ceil(_width * inv_cell_size)), grid_height(std::ceil(_height * inv_cell_size)),
            grid(grid_height, std::vector<int>(grid_width, -1))
        {}

        bool operator() (Vec<2> &next_point);

        inline const std::vector<Vec<2>> &getPoints (void) const { return this->points; }
        const std::vector<Vec<2>> &allPoints (void);

    };

}


#endif
