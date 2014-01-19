#include <windows.h>
#include <d3d9.h>

#include "colour.hh"
#include "device.hh"
#include "enums.hh"
#include "error.hh"
#include "matrix.hh"
#include "scene.hh"
#include "vertexbuffer.hh"
#include "window.hh"

namespace d3d9 {

Scene::Scene(const Device &dev, const HWND hwnd, const Colour background)
    : dev_(dev), background_{background}, hwnd_{hwnd} {
    clearTarget();
    clearZBuffer();

    HRESULT hr;
    if (FAILED(hr = dev_.d3d()->BeginScene())) {
        throw Exception(hr, "Failed to begin scene.", D3D9_ERROR_LOCATION);
    }
}

Scene::~Scene() {
    if (!ended_) {
        try {
            present();
        } catch (Exception &) {}
    }
}

void Scene::present() {
    HRESULT hr;
    if (FAILED(hr = dev_.d3d()->EndScene())) {
        throw Exception(hr, "Failed to end scene.", D3D9_ERROR_LOCATION);
    }

    ended_ = true;

    if (FAILED(hr = dev_.d3d()->Present(nullptr, nullptr, hwnd_, nullptr))) {
        if (hr == D3DERR_DEVICELOST) {
            SendMessage(hwnd_, Message::ResetDevice, 0, reinterpret_cast<LPARAM>(&dev_));
        } else if ((hr & 0x7FFFFFFF) != MAKE_D3DSTATUS(0x872)) { //unknown error while resizing in multithreaded mode
            throw Exception(hr, "Failed to present scene.", D3D9_ERROR_LOCATION);
        }
    }
}

void Scene::clear(const DWORD count, const D3DRECT *const rects, const DWORD flags, const Colour background, const double z, const DWORD stencil) const {
    HRESULT hr;
    if (FAILED(hr = dev_.d3d()->Clear(count, rects, flags, d3d(background), z, stencil))) {
        throw Exception(hr, D3D9_ERROR_LOCATION);
    }
}

void Scene::clearTarget() const {clearTarget(background_);}
void Scene::clearTarget(const Colour background) const {clear(0, nullptr, D3DCLEAR_TARGET, background, 1, 0);}
void Scene::clearZBuffer() const {clearZBuffer(background_);}
void Scene::clearZBuffer(const Colour background) const {clear(0, nullptr, D3DCLEAR_ZBUFFER, background, 1, 0);}

void Scene::worldTransform(const Matrix &mat) const {setTransform(TransformStateType::World, mat);}
void Scene::viewTransform(const Matrix &mat) const {setTransform(TransformStateType::View, mat);}
void Scene::projectionTransform(const Matrix &mat) const {setTransform(TransformStateType::Projection, mat);}

void Scene::setTransform(const TransformStateType type, const Matrix &mat) const {
    HRESULT hr;
    if (FAILED(hr = dev_.d3d()->SetTransform(static_cast<D3DTRANSFORMSTATETYPE>(static_cast<int>(type)), &mat.d3d()))) {
        throw Exception(hr, D3D9_ERROR_LOCATION);
    }
}

}
