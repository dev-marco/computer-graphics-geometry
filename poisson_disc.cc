#include "poisson_disc.h"

namespace Geometry {

    std::mt19937 PoissonDisc::random_generator(std::chrono::system_clock::now().time_since_epoch().count());

    void PoissonDisc::randomSinCos (float_max_t &random_sin, float_max_t &random_cos) {
        static std::bernoulli_distribution sin_signal(0.5);
        static std::uniform_real_distribution<float_max_t> cos_generator(-1.0, 1.0);

        random_cos = cos_generator(PoissonDisc::random_generator);

        if (sin_signal(PoissonDisc::random_generator)) {
            random_sin = -std::sqrt(1.0 - (random_cos * random_cos));
        } else {
            random_sin = std::sqrt(1.0 - (random_cos * random_cos));
        }
    }

    bool PoissonDisc::validPoint (const Vec<2> &point) {

        if (0.0 <= point[0] && point[0] < this->width &&
            0.0 <= point[1] && point[1] < this->height) {

            const unsigned
                pos_x = point[0] * this->inv_cell_size,
                pos_y = point[1] * this->inv_cell_size,
                min_x = pos_x > 2 ? (pos_x - 2) : 0,
                min_y = pos_y > 2 ? (pos_y - 2) : 0,
                max_x = std::min(pos_x + 3, this->grid_width),
                max_y = std::min(pos_y + 3, this->grid_height);

            for (unsigned y = min_y; y < max_y; ++y) {

                const std::vector<int> &line = this->grid[y];

                for (unsigned x = min_x; x < max_x; ++x) {
                    if (line[x] >= 0) {
                        if (point.distance2(this->points[line[x]]) < this->radius2) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }

        return false;
    }

    void PoissonDisc::addPoint (const Vec<2> &point) {
        unsigned position = this->points.size();
        this->points.push_back(point);
        this->queue.push_back(position);
        this->grid[static_cast<unsigned>(point[1] * inv_cell_size)]
            [static_cast<unsigned>(point[0] * inv_cell_size)] = position;
    }

    bool PoissonDisc::operator() (Vec<2> &next_point) {

        if (this->points.empty()) {
            std::uniform_real_distribution<float_max_t> position_x(0.0, this->width), position_y(0.0, this->height);
            next_point = { position_x(PoissonDisc::random_generator), position_y(PoissonDisc::random_generator) };
            this->addPoint(next_point);
            return true;
        }

        std::vector<int>::reverse_iterator next;

        for (auto it = this->queue.rbegin(); it != this->queue.rend(); it = next) {
            std::uniform_real_distribution<float_max_t> generate_radius(this->radius, this->two_radius);

            const Vec<2> &close = this->points[*it];

            for (unsigned i = 0; i < this->samples; ++i) {
                const float_max_t radius = generate_radius(PoissonDisc::random_generator);
                float_max_t angle_cos, angle_sin;

                randomSinCos(angle_sin, angle_cos);

                const Vec<2> point = { close[0] + angle_cos * radius, close[1] + angle_sin * radius };

                if (validPoint(point)) {
                    next_point = point;
                    this->addPoint(point);
                    return true;
                }
            }

            next = std::next(it);

            std::swap(*it, this->queue.back());
            this->queue.pop_back();
        }

        return false;
    }

    const std::vector<Vec<2>> &PoissonDisc::allPoints (void) {
        Vec<2> point;
        while ((*this)(point));
        return this->points;
    }

};
