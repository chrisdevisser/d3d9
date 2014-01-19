#ifndef D3D9_VERTICES_H
#define D3D9_VERTICES_H

#include <d3d9.h>
#include "colour.hh"

namespace d3d9 {

struct XyzRhwDiffuseVertex {
    static constexpr DWORD Fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

    XyzRhwDiffuseVertex() = default; //needed for trivial class requirement for POD for memcpy
    XyzRhwDiffuseVertex(double x_, double y_, double z_, double rhw_, Colour diffuse_)
        : x(x_), y(y_), z(z_), rhw(rhw_), diffuse{d3d(diffuse_)} {}

    float x, y, z, rhw;
    D3DCOLOR diffuse;
};

struct XyzDiffuseVertex {
    static constexpr DWORD Fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

    XyzDiffuseVertex() = default;
    XyzDiffuseVertex(double x_, double y_, double z_, Colour diffuse_)
        : x(x_), y(y_), z(z_), diffuse{d3d(diffuse_)} {}

    float x, y, z;
    D3DCOLOR diffuse;
};

}

#endif
