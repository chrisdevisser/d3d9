#ifndef D3D9_VERTEXBUFFER_H
#define D3D9_VERTEXBUFFER_H

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include <d3d9.h>

#include "device.hh"
#include "error.hh"
#include <dxutil/comptr.hh>

namespace d3d9 {

template<typename Vertex>
struct VertexBuffer {
    static_assert(std::is_pod<Vertex>::value, "Vertex type must be POD.");

    VertexBuffer(const Device &dev, const std::vector<Vertex> &buffer)
        : vertices_(buffer) {
        HRESULT hr;
        if (FAILED(hr = dev.d3d()->CreateVertexBuffer(buffer.size() * sizeof(Vertex), 0, Vertex::Fvf, D3DPOOL_MANAGED, buffer_.address(), nullptr))) {
            throw Exception(hr, "Failed to create vertex buffer.", D3D9_ERROR_LOCATION);
        }

        adjust(buffer);
    }

    void adjust(const std::vector<Vertex> &newData, unsigned pos = 0) {
        if (pos > vertices_.size() - newData.size()) {
            throw std::out_of_range("Attempted to adjust out of bounds.");
        }

        void *data;
        HRESULT hr;
        if (FAILED(hr = buffer_->Lock(pos * sizeof(Vertex), newData.size() * sizeof(Vertex), &data, 0))) {
            throw Exception(hr, "Failed to lock vertex buffer.", D3D9_ERROR_LOCATION);
        }

        memcpy(data, newData.data(), newData.size() * sizeof(Vertex));

        if (FAILED(hr = buffer_->Unlock())) {
            throw Exception(hr, "Failed to unlock vertex buffer.", D3D9_ERROR_LOCATION);
        }
    }

    IDirect3DVertexBuffer9 *d3d() const {
        return buffer_.get();
    }

private:
    DxUtil::ComPtr<IDirect3DVertexBuffer9> buffer_;
    std::vector<Vertex> vertices_;
};

}

#endif
