//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_SCENE_H
#define D3D9_SCENE_H

#include <d3d9.h>

#include "colour.h"
#include "device.h"
#include "enums.h"
#include "error.h"
#include "vertexbuffer.h"
#include "window.h"

namespace d3d9 {

struct Scene {
    Scene(const Device &dev, HWND hwnd, Colour c = {255, 0, 0, 0})
        : dev_(dev), col_{c}, hwnd_{hwnd} {
        clearTarget();
        clearZBuffer();

        HRESULT hr;
        if (FAILED(hr = dev_.get()->BeginScene())) {
            throw Exception(hr, "Failed to begin scene.", D3D9_ERROR_LOCATION);
        }
    }

    Scene(const Scene &) = delete;

    ~Scene() {
        if (!ended_) {
            try {
                present();
            } catch (Exception &) {}
        }
    }

    void present() {
        HRESULT hr;
        if (FAILED(hr = dev_.get()->EndScene())) {
            throw Exception(hr, "Failed to end scene.", D3D9_ERROR_LOCATION);
        }

        ended_ = true;

        if (FAILED(hr = dev_.get()->Present(nullptr, nullptr, hwnd_, nullptr))) {
            if (hr == D3DERR_DEVICELOST) {
                SendMessage(hwnd_, detail::Message::ResetDevice, 0, reinterpret_cast<LPARAM>(&dev_));
            } else if (hr != MAKE_D3DSTATUS(0x801)) { //unknown error while resizing in multithreaded mode
                throw Exception(hr, "Failed to present scene.", D3D9_ERROR_LOCATION);
            }
        }
    }

    void clear(DWORD count, D3DRECT *rects, DWORD flags, D3DCOLOR colour, double z, DWORD stencil) const {
        HRESULT hr;
        if (FAILED(hr = dev_.get()->Clear(count, rects, flags, colour, z, stencil))) {
            throw Exception(hr, D3D9_ERROR_LOCATION);
        }
    }

    void clearTarget() const {
        clear(0, nullptr, D3DCLEAR_TARGET, col_.d3d(), 1, 0);
    }

    void clearTarget(Colour c) const {
        clear(0, nullptr, D3DCLEAR_TARGET, c.d3d(), 1, 0);
    }

    void clearZBuffer() const {
        clear(0, nullptr, D3DCLEAR_ZBUFFER, col_.d3d(), 1, 0);
    }

    void clearZBuffer(Colour c) const {
        clear(0, nullptr, D3DCLEAR_ZBUFFER, c.d3d(), 1, 0);
    }

    void worldTransform(const Matrix &mat) const {
        setTransform(D3DTS_WORLD, &mat.get());
    }

    void viewTransform(const Matrix &mat) const {
        setTransform(D3DTS_VIEW, &mat.get());
    }

    void projectionTransform(const Matrix &mat) const {
        setTransform(D3DTS_PROJECTION, &mat.get());
    }

    template<typename T>
    void draw(const VertexBuffer<T> &buffer, PrimitiveType type, std::size_t num) {
        HRESULT hr;
        if (FAILED(hr = dev_.get()->SetFVF(VertexBuffer<T>::Fvf))) {
            throw Exception(hr, "Failed to set FVF.", D3D9_ERROR_LOCATION);
        }

        if (FAILED(hr = dev_.get()->SetStreamSource(0, buffer.get(), 0, sizeof(T)))) {
            throw Exception(hr, "Failed to set stream source.", D3D9_ERROR_LOCATION);
        }

        if (FAILED(hr = dev_.get()->DrawPrimitive(static_cast<D3DPRIMITIVETYPE>(static_cast<int>(type)), 0, num))) {
            throw Exception(hr, "Failed to draw primitive.", D3D9_ERROR_LOCATION);
        }
    }

private:
    Device dev_;
    Colour col_;
    HWND hwnd_;
    bool ended_{};

    void setTransform(D3DTRANSFORMSTATETYPE type, const D3DXMATRIX *mat) const {
        HRESULT hr;
        if (FAILED(hr = dev_.get()->SetTransform(type, mat))) {
            throw Exception(hr, D3D9_ERROR_LOCATION);
        }
    }
};

}

#endif
