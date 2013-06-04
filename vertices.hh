//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_VERTICES_H
#define D3D9_VERTICES_H

#include <d3d9.h>

namespace d3d9 {

struct XyzRhwDiffuseVertex {
    static constexpr DWORD Fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

    XyzRhwDiffuseVertex() = default; //needed for trivial class requirement for POD for memcpy
    XyzRhwDiffuseVertex(double x_, double y_, double z_, double rhw_, Colour diffuse_)
        : x(x_), y(y_), z(z_), rhw(rhw_), diffuse{diffuse_.d3d()} {}

    float x, y, z, rhw;
    D3DCOLOR diffuse;
};

struct XyzDiffuseVertex {
    static constexpr DWORD Fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

    XyzDiffuseVertex() = default;
    XyzDiffuseVertex(double x_, double y_, double z_, Colour diffuse_)
        : x(x_), y(y_), z(z_), diffuse{diffuse_.d3d()} {}

    float x, y, z;
    D3DCOLOR diffuse;
};

}

#endif
