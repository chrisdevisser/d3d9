//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_VERTEXBUFFER_H
#define D3D9_VERTEXBUFFER_H

#include <cstddef>
#include <stdexcept>
#include <vector>

#include <d3d9.h>

#include "comptr.h"
#include "device.h"
#include "error.h"
#include <type_traits>
#include "error.h"
#include "vertices.h"

namespace d3d9 {

template<typename T>
struct VertexBuffer {
    static_assert(std::is_pod<T>::value, "Vertex type must be POD.");

    static constexpr DWORD Fvf = T::Fvf;

    VertexBuffer(const Device &dev, const std::vector<T> &buffer)
        : vertices_(buffer) {
        HRESULT hr;
        if (FAILED(hr = dev.get()->CreateVertexBuffer(buffer.size() * sizeof(T), 0, Fvf, D3DPOOL_MANAGED, buffer_.address(), nullptr))) {
            throw Exception(hr, "Failed to create vertex buffer.", D3D9_ERROR_LOCATION);
        }

        adjust(buffer);
    }

    void adjust(const std::vector<T> &newData, unsigned pos = 0) {
        if (pos > vertices_.size() - newData.size()) {
            throw std::out_of_range("Attempted to adjust out of bounds.");
        }

        void *data;
        HRESULT hr;
        if (FAILED(hr = buffer_->Lock(pos * sizeof(T), newData.size() * sizeof(T), &data, 0))) {
            throw Exception(hr, "Failed to lock vertex buffer.", D3D9_ERROR_LOCATION);
        }

        memcpy(data, newData.data(), newData.size() * sizeof(T));

        if (FAILED(hr = buffer_->Unlock())) {
            throw Exception(hr, "Failed to unlock vertex buffer.", D3D9_ERROR_LOCATION);
        }
    }

    IDirect3DVertexBuffer9 *get() const {
        return buffer_.get();
    }

private:
    DxUtil::ComPtr<IDirect3DVertexBuffer9> buffer_;
    std::vector<T> vertices_;
};

}

#endif
