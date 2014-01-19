#include <string>

#include <windows.h>
#include <d3dx9.h>

#include "matrix.hh"
#include "perspective.hh"
#include <stdx/angle.hh>

namespace d3d9 {

//do NOT change to near and far. windows.h #defines them
d3d9::Perspective::Perspective(stdx::Angle fov, HWND hwnd, double _near, double _far) noexcept
    : fov_{fov}, hwnd_{hwnd}, near_(_near), far_(_far) {}

Matrix Perspective::matrix() const noexcept {
    RECT client;
    GetClientRect(hwnd_, &client);

    int width = client.right - client.left;
    int height = client.bottom - client.top;

    Matrix ret;
    D3DXMatrixPerspectiveFovLH(&ret.d3d(), fov_.rad(), width * 1. / height, near_, far_);
    return ret;
}

}

