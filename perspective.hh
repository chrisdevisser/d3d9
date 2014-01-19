//Represents a perspective with the ability to get the perspective matrix.

#ifndef D3D9_PERSPECTIVE_H
#define D3D9_PERSPECTIVE_H

#include <windows.h>
#include <stdx/angle.hh>

namespace d3d9 {

class Matrix;

struct Perspective {
    Perspective(stdx::Angle fov, HWND hwnd, double _near, double _far) noexcept;
    Matrix matrix() const noexcept;

private:
    stdx::Angle fov_;
    HWND hwnd_;
    double near_;
    double far_;
};

}

#endif
