//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_DIRECT3D_H
#define D3D9_DIRECT3D_H

#include <d3d9.h>

#include "comptr.h"
#include "error.h"

namespace d3d9 {

struct Direct3D {
    Direct3D() {
        if (!d3d9_) {
            throw Exception(-1, "Failed to create IDirect3D9 interface.", D3D9_ERROR_LOCATION);
        }
    }

    Direct3D(IDirect3D9 *iface)
        : d3d9_{iface} {}

    IDirect3D9 *get() const {
        return d3d9_.get();
    }

private:
    DxUtil::ComPtr<IDirect3D9> d3d9_{Direct3DCreate9(D3D_SDK_VERSION)};
};

}

#endif
