#include "transformed_shape.h"

namespace Geometry {

    constexpr std::array<float_max_t, 16> TransformedShape::identity;

    void TransformedShape::makeInverse (void) {

        const std::array<float_max_t, 16> &m = this->getMatrix();

        this->inv_matrix[0] =
            m[5] * (m[10] * m[15] - m[11] * m[14]) +
            m[9] * (m[7] * m[14] - m[6] * m[15]) +
            m[13] * (m[6] * m[11] - m[7] * m[10]);

        this->inv_matrix[4] =
            m[4] * (m[11] * m[14] - m[10] * m[15]) +
            m[8] * (m[6] * m[15] - m[7] * m[14]) +
            m[12] * (m[7] * m[10] - m[6] * m[11]);

        this->inv_matrix[8] =
            m[4] * (m[9] * m[15] - m[11] * m[13]) +
            m[8] * (m[7] * m[13] - m[5] * m[15]) +
            m[12] * (m[5] * m[11] - m[7] * m[9]);

        this->inv_matrix[12] =
            m[4] * (m[10] * m[13] - m[9] * m[14]) +
            m[8] * (m[5] * m[14] - m[6] * m[13]) +
            m[12] * (m[6] * m[9] - m[5] * m[10]);

        const float_max_t det =
            m[0] * this->inv_matrix[ 0] + m[1] * this->inv_matrix[ 4] +
            m[2] * this->inv_matrix[ 8] + m[3] * this->inv_matrix[12];

        if (det != 0.0) {

            const float_max_t det_inv = 1.0 / det;

            this->inv_matrix[0] *= det_inv, this->inv_matrix[ 4] *= det_inv;
            this->inv_matrix[8] *= det_inv, this->inv_matrix[12] *= det_inv;

            this->inv_matrix[1] = (
                m[1] * (m[11] * m[14] - m[10] * m[15]) +
                m[9] * (m[2] * m[15] - m[3] * m[14]) +
                m[13] * (m[3] * m[10] - m[2] * m[11])
            ) * det_inv;

            this->inv_matrix[5] = (
                m[0] * (m[10] * m[15] - m[11] * m[14]) +
                m[8] * (m[3] * m[14] - m[2] * m[15]) +
                m[12] * (m[2] * m[11] - m[3] * m[10])
            ) * det_inv;

            this->inv_matrix[9] = (
                m[0] * (m[11] * m[13] - m[9] * m[15]) +
                m[8] * (m[1] * m[15] - m[3] * m[13]) +
                m[12] * (m[3] * m[9] - m[1] * m[11])
            ) * det_inv;

            this->inv_matrix[13] = (
                m[0] * (m[9] * m[14] - m[10] * m[13]) +
                m[8] * (m[2] * m[13] - m[1] * m[14]) +
                m[12] * (m[1] * m[10] - m[2] * m[9])
            ) * det_inv;

            this->inv_matrix[2] = (
                m[1] * (m[6] * m[15] - m[7] * m[14]) +
                m[5] * (m[3] * m[14] - m[2] * m[15]) +
                m[13] * (m[2] * m[7] - m[3] * m[6])
            ) * det_inv;

            this->inv_matrix[6] = (
                m[0] * (m[7] * m[14] - m[6] * m[15]) +
                m[4] * (m[2] * m[15] - m[3] * m[14]) +
                m[12] * (m[3] * m[6] - m[2] * m[7])
            ) * det_inv;

            this->inv_matrix[10] = (
                m[0] * (m[5] * m[15] - m[7] * m[13]) +
                m[4] * (m[3] * m[13] - m[1] * m[15]) +
                m[12] * (m[1] * m[7] - m[3] * m[5])
            ) * det_inv;

            this->inv_matrix[14] = (
                m[0] * (m[6] * m[13] - m[5] * m[14]) +
                m[4] * (m[1] * m[14] - m[2] * m[13]) +
                m[12] * (m[2] * m[5] - m[1] * m[6])
            ) * det_inv;

            this->inv_matrix[3] = (
                m[1] * (m[7] * m[10] - m[6] * m[11]) +
                m[5] * (m[2] * m[11] - m[3] * m[10]) +
                m[9] * (m[3] * m[6] - m[2] * m[7])
            ) * det_inv;

            this->inv_matrix[7] = (
                m[0] * (m[6] * m[11] - m[7] * m[10]) +
                m[4] * (m[3] * m[10] - m[2] * m[11]) +
                m[8] * (m[2] * m[7] - m[3] * m[6])
            ) * det_inv;

            this->inv_matrix[11] = (
                m[0] * (m[7] * m[9] - m[5] * m[11]) +
                m[4] * (m[1] * m[11] - m[3] * m[9]) +
                m[8] * (m[3] * m[5] - m[1] * m[7])
            ) * det_inv;

            this->inv_matrix[15] = (
                m[0] * (m[5] * m[10] - m[6] * m[9]) +
                m[4] * (m[2] * m[9] - m[1] * m[10]) +
                m[8] * (m[1] * m[6] - m[2] * m[5])
            ) * det_inv;
        } else {
            throw std::domain_error("Invalid transformation matrix.");
        }
    }

    void TransformedShape::makeTransposed (void) {
        const std::array<float_max_t, 16> inv = this->getMatrixInverse();
        this->inv_trans_matrix = {
            inv[0], inv[4], inv[8], inv[12],
            inv[1], inv[5], inv[9], inv[13],
            inv[2], inv[6], inv[10], inv[14],
            inv[3], inv[7], inv[11], inv[15]
        };
    }

    void TransformedShape::multiplyMatrix (const std::array<float_max_t, 16> &other) {
        std::array<float_max_t, 16> result;
        bool not_identity = false;
        for (unsigned i = 0; i < 16; ++i) {
            if (i == 0 || i == 5 || i == 10 || i == 15) {
                if (i != 1.0) {
                    not_identity = true;
                    break;
                }
            } else if (closeToZero(i)) {
                not_identity = true;
                break;
            }
        }
        if (not_identity) {
            for (unsigned i = 0; i < 16; i += 4) {
                for (unsigned j = 0; j < 4; ++j) {
                    result[i + j] =
                        this->matrix[i] * other[j] +
                        this->matrix[i + 1] * other[j + 4] +
                        this->matrix[i + 2] * other[j + 8] +
                        this->matrix[i + 3] * other[j + 12];
                }
            }
            this->matrix.swap(result);
            this->updateMatrixes();
        }
    }

    void TransformedShape::scale (float_max_t sx, float_max_t sy, float_max_t sz) {
        if (sx != 1.0 || sy != 1.0 || sz != 1.0) {
            this->multiplyMatrix({
                 sx, 0.0, 0.0, 0.0,
                0.0,  sy, 0.0, 0.0,
                0.0, 0.0,  sz, 0.0,
                0.0, 0.0, 0.0, 1.0
            });
        }
    }

    void TransformedShape::shear (float_max_t sxy, float_max_t sxz, float_max_t syx, float_max_t syz, float_max_t szx, float_max_t szy) {
        if (sxy != 0.0 || sxz != 0.0 || syx != 0.0 || syz != 0.0 || szx != 0.0 || szy != 0.0) {
            this->multiplyMatrix({
                1.0, sxy, sxz, 0.0,
                syx, 1.0, syz, 0.0,
                szx, szy, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0
            });
        }
    }

    void TransformedShape::rotate (const Quaternion &quat) {
        if (!quat.isIdentity()) {
            this->multiplyMatrix(quat.rotation());
        }
    }

    void TransformedShape::translate (float_max_t tx, float_max_t ty, float_max_t tz) {
        if (tx != 0.0 || ty != 0.0 || tz != 0.0) {
            this->multiplyMatrix({
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                 tx,  ty,  tz, 1.0
            });
        }
    }

    const Shape *TransformedShape::boundingVolume (void) const {
        const Shape *bound = shape->boundingVolume();
        if (bound == this->getShape()) {
            return this;
        }
        return new TransformedShape(bound, this->getPivot(), this->getMatrix(), this->getMatrixInverse(), this->getMatrixInverseTransposed());
    }

    bool TransformedShape::intersectLine (const Line &line, Vec<3> &normal_min, Vec<3> &normal_max, float_max_t &t_min, float_max_t &t_max, bool fix_normals) const {
        static Line transf_line;
        transf_line = Line(line.getPoint().transformed(this->getMatrixInverse(), this->getPivot()), line.getDirection().transformedNormal(this->getMatrixInverse()));
        if (this->getShape()->intersectLine(transf_line, normal_min, normal_max, t_min, t_max, fix_normals)) {
            normal_min.transform(this->getMatrixInverseTransposed());
            normal_max.transform(this->getMatrixInverseTransposed());
            return true;
        }
        return false;
    }



};
