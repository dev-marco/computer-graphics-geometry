#ifndef MODULE_GEOMETRY_CAMERA_H_
#define MODULE_GEOMETRY_CAMERA_H_

#include "defaults.h"
#include "vec.h"
#include "quaternion.h"

namespace Geometry {

    class Camera {
        Geometry::Vec<3> position, look_at, up_dir;
        float_max_t fov;

    public:
        Camera (void) {}

        Camera (const Vec<3> &_position, const Vec<3> &_look_at, const Vec<3> &_up_dir, const float_max_t &_fov) :
            position(_position), look_at(_look_at), up_dir(_up_dir), fov(_fov) {}

        inline const Geometry::Vec<3> &getPosition (void) const { return this->position; }
        inline const Geometry::Vec<3> &getLookAt (void) const { return this->look_at; }
        inline const Geometry::Vec<3> &getUpDirection (void) const { return this->up_dir; }
        inline const float_max_t &getFieldOfView (void) const { return this->fov; }

        inline void setPosition (const Geometry::Vec<3> &_position) { this->position = _position; }
        inline void lookAt (const Geometry::Vec<3> &_look_at) { this->look_at = _look_at; }
        inline void setUpDirection (const Geometry::Vec<3> &_up_dir) { this->up_dir = _up_dir.normalized(); }
        inline void setFieldOfView (const float_max_t &_fov) { this->fov = _fov; }

        inline void rotate (const Geometry::Quaternion &rot) { rot.rotate(this->look_at, this->getPosition()); }
    };
}

#endif
