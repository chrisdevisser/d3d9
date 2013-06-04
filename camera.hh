//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

//Performs operations related to a camera.

#ifndef D3D9_CAMERA_H
#define D3D9_CAMERA_H

#include <d3dx9.h>
#include "matrix.h"
#include "vector.h"

namespace d3d9 {

struct Camera {
    Camera(Vector3 eye = {0, 0, -100}, Vector3 at = {}, Vector3 up = {0, 1, 0})
        : eye_{eye}, at_{at}, up_{up} {}

    Matrix matrix() const {
        Matrix ret;
        return *D3DXMatrixLookAtLH(&ret.get(), &eye_.get(), &at_.get(), &up_.get());
    }

    Camera &moveTo(double x, double y, double z) {
        eye_ = {x, y, z};
        return *this;
    }

    Camera &move(double x, double y, double z) {
        eye_ += {x, y, z};
        return *this;
    }

    Camera &swingTo(double x, double y, double z) {
        at_ = {x, y, z};
        return *this;
    }

    Camera &swing(double x, double y, double z) {
        at_ += {x, y, z};
        return *this;
    }

    Camera &turnTo(double x, double y, double z) {
        up_ = {x, y, z};
        return *this;
    }

private:
    Vector3 eye_;
    Vector3 at_;
    Vector3 up_;
};

}

#endif
