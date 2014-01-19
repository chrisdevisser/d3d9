#include <d3d9.h>
#include "direct3d.hh"
#include "error.hh"
#include <dxutil/comptr.hh>

namespace d3d9 {

Direct3D::Direct3D()
    : d3d9_{Direct3DCreate9(D3D_SDK_VERSION)} {
    if (!d3d9_) throw Exception(-1, "Failed to create IDirect3D9 interface.", D3D9_ERROR_LOCATION);
}

Direct3D::Direct3D(IDirect3D9 *const iface) noexcept : d3d9_{iface} {}
IDirect3D9 *Direct3D::d3d() const noexcept {return d3d9_.get();}

}

