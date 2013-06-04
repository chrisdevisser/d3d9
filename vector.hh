//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_VECTOR_H
#define D3D9_VECTOR_H

#include <d3dx9.h>

namespace d3d9 {

struct Vector3 {
    Vector3()
        : Vector3{0, 0, 0} {}

    Vector3(double x, double y, double z)
        : vec_(x, y, z) {}

    Vector3(const D3DXVECTOR3 &vec)
        : vec_{vec} {}

    Vector3 &operator+=(const Vector3 &other) {
        vec_ += other.vec_;
        return *this;
    }

    const D3DXVECTOR3 &get() const {
        return vec_;
    }

    D3DXVECTOR3 &get() {
        return vec_;
    }

private:
    D3DXVECTOR3 vec_;
};

Vector3 operator+(Vector3 lhs, const Vector3 &rhs) {
    return lhs += rhs;
}

}

#endif
