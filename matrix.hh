//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_MATRIX_H
#define D3D9_MATRIX_H

#include <utility>
#include <d3dx9.h>
#include "angle.h"

namespace d3d9 {

struct Matrix {
    Matrix() {
        D3DXMatrixIdentity(&mat_);
    }

    Matrix(const D3DXMATRIX &mat)
        : mat_{mat} {}

    Matrix &operator*=(const Matrix &other) {
        mat_ *= other.mat_;
        return *this;
    }

    Matrix &translate(double x, double y, double z) {
        applyTransformation(D3DXMatrixTranslation, x, y, z);
        return *this;
    }

    Matrix &rotateX(stdx::Angle angle) {
        applyTransformation(D3DXMatrixRotationX, angle.rad());
        return *this;
    }

    Matrix &rotateY(stdx::Angle angle) {
        applyTransformation(D3DXMatrixRotationY, angle.rad());
        return *this;
    }

    Matrix &rotateZ(stdx::Angle angle) {
        applyTransformation(D3DXMatrixRotationZ, angle.rad());
        return *this;
    }

    Matrix &scale(double x, double y, double z) {
        applyTransformation(D3DXMatrixScaling, x, y, z);
        return *this;
    }

    const D3DXMATRIX &get() const {
        return mat_;
    }

    D3DXMATRIX &get() {
        return mat_;
    }

private:
    D3DXMATRIX mat_;

    template<typename F, typename... Args>
    void applyTransformation(F &&f, Args&&... args) {
        D3DXMATRIX temp;
        f(&temp, std::forward<Args>(args)...);
        mat_ *= temp;
    }
};

Matrix operator*(Matrix lhs, const Matrix &rhs) {
    return lhs *= rhs;
}

}

#endif
