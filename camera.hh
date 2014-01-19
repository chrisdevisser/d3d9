//Performs operations related to a camera.

#ifndef D3D9_CAMERA_H
#define D3D9_CAMERA_H

#include "vector.hh"

namespace d3d9 {

class Matrix;

struct Camera {
    Camera(const Vector3 &_eye = {0, 0, -100}, const Vector3 &_at = {}, const Vector3 &_up = {0, 1, 0}) noexcept;

    Matrix matrix() const noexcept;

    Camera &moveTo(double x, double y, double z) noexcept; //eye
    Camera &move(double x, double y, double z) noexcept;
    Camera &swingTo(double x, double y, double z) noexcept; //at
    Camera &swing(double x, double y, double z) noexcept;
    Camera &turnTo(double x, double y, double z) noexcept; //up
    Camera &turn(double x, double y, double z) noexcept;

    Vector3 eye() const noexcept;
    Vector3 at() const noexcept;
    Vector3 up() const noexcept;

private:
    Vector3 eye_;
    Vector3 at_;
    Vector3 up_;
};

}

#endif
