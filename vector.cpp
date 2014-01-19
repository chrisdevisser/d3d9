#ifndef D3D9_VECTOR_H
#define D3D9_VECTOR_H

#include <d3dx9.h>

//TODO add stuff

namespace d3d9 {

struct Vector3 {
    Vector3() noexcept
        : Vector3{0, 0, 0} {}

    Vector3(double x, double y, double z) noexcept
        : vec_(x, y, z) {}

    Vector3(const D3DXVECTOR3 &vec) noexcept
        : vec_{vec} {}

    Vector3 &operator+=(const Vector3 &other) noexcept {
        vec_ += other.vec_;
        return *this;
    }

    const D3DXVECTOR3 &d3d() const noexcept {
        return vec_;
    }

    D3DXVECTOR3 &d3d() noexcept {
        return vec_;
    }

private:
    D3DXVECTOR3 vec_;
};

inline Vector3 operator+(Vector3 lhs, const Vector3 &rhs) noexcept {
    return lhs += rhs;
}

}

#endif

