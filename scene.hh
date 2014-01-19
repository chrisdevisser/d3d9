//Represents a 3D scene.

#ifndef D3D9_SCENE_H
#define D3D9_SCENE_H

#include <cstddef>
#include <windows.h>
#include <d3d9.h>

#include "colour.hh"
#include "device.hh"
#include "enums.hh"
#include "error.hh"

namespace d3d9 {

class Matrix;
template<typename Vertex> class VertexBuffer;

struct Scene {
    Scene(const Device &dev, HWND hwnd, Colour background = Colours::Black);
    Scene(const Scene &) = delete;
    ~Scene() noexcept;

    void present();

    void clear(DWORD count, const D3DRECT *rects, DWORD flags, Colour colour, double z, DWORD stencil) const;
    void clearTarget() const;
    void clearTarget(Colour background) const;
    void clearZBuffer() const;
    void clearZBuffer(Colour background) const;
    void worldTransform(const Matrix &mat) const;
    void viewTransform(const Matrix &mat) const;
    void projectionTransform(const Matrix &mat) const;

    template<typename Vertex>
    void draw(const VertexBuffer<Vertex> &buffer, PrimitiveType type, std::size_t num) const;

private:
    Device dev_;
    Colour background_;
    HWND hwnd_;
    bool ended_{};

    void setTransform(TransformStateType type, const Matrix &mat) const;
};

template<typename Vertex>
void Scene::draw(const VertexBuffer<Vertex> &buffer, PrimitiveType type, std::size_t num) const {
    HRESULT hr;
    if (FAILED(hr = dev_.d3d()->SetFVF(Vertex::Fvf))) {
        throw Exception(hr, "Failed to set FVF.", D3D9_ERROR_LOCATION);
    }

    if (FAILED(hr = dev_.d3d()->SetStreamSource(0, buffer.d3d(), 0, sizeof(Vertex)))) {
        throw Exception(hr, "Failed to set stream source.", D3D9_ERROR_LOCATION);
    }

    if (FAILED(hr = dev_.d3d()->DrawPrimitive(static_cast<D3DPRIMITIVETYPE>(static_cast<int>(type)), 0, num))) {
        throw Exception(hr, "Failed to draw primitive.", D3D9_ERROR_LOCATION);
    }
}

}

#endif
