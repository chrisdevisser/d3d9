//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_PERSPECTIVE_H
#define D3D9_PERSPECTIVE_H

#include <string>
#include <d3d9.h>
#include "angle.h"
#include "error.h"
#include "matrix.h"

namespace d3d9 {

struct Perspective {
    Perspective(stdx::Angle fov, HWND hwnd, double n, double f)
        : fov_{fov}, hwnd_{hwnd}, near_(n), far_(f) {}

    Matrix matrix() const {
        Matrix ret;

        RECT client;
        GetClientRect(hwnd_, &client);

        int width = client.right - client.left;
        int height = client.bottom - client.top;

        D3DXMatrixPerspectiveFovLH(&ret.get(), fov_.rad(), width * 1. / height, near_, far_);
        return ret;
    }

private:
    stdx::Angle fov_;
    HWND hwnd_;
    double near_;
    double far_;
};

}

#endif
