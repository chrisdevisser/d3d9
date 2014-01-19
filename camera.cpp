#include <d3dx9.h>
#include "camera.hh"
#include "matrix.hh"
#include "vector.hh"

namespace d3d9 {

Camera::Camera(const Vector3 &_eye, const Vector3 &_at, const Vector3 &_up) noexcept
    : eye_{_eye}, at_{_at}, up_{_up} {}

Matrix Camera::matrix() const noexcept {
    Matrix ret;
    return *D3DXMatrixLookAtLH(&ret.d3d(), &eye_.d3d(), &at_.d3d(), &up_.d3d());
}

Camera &Camera::moveTo(const double x, const double y, const double z) noexcept {
    eye_ = {x, y, z};
    return *this;
}

Camera &Camera::move(const double x, const double y, const double z) noexcept {
    eye_ += {x, y, z};
    return *this;
}

Camera &Camera::swingTo(const double x, const double y, const double z) noexcept {
    at_ = {x, y, z};
    return *this;
}

Camera &Camera::swing(const double x, const double y, const double z) noexcept {
    at_ += {x, y, z};
    return *this;
}

Camera &Camera::turnTo(const double x, const double y, const double z) noexcept {
    up_ = {x, y, z};
    return *this;
}

Camera &Camera::turn(const double x, const double y, const double z) noexcept {
    up_ += {x, y, z};
    return *this;
}

Vector3 Camera::eye() const noexcept {return eye_;}
Vector3 Camera::at() const noexcept {return at_;}
Vector3 Camera::up() const noexcept {return up_;}

}
