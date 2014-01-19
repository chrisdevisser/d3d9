//Represents IDirect3D9

#ifndef D3D9_DIRECT3D_H
#define D3D9_DIRECT3D_H

#include <dxutil/comptr.hh>

class IDirect3D9;

namespace d3d9 {

struct Direct3D {
    Direct3D();
    Direct3D(IDirect3D9 *iface) noexcept;
    IDirect3D9 *d3d() const noexcept;

private:
    DxUtil::ComPtr<IDirect3D9> d3d9_;
};

}

#endif
