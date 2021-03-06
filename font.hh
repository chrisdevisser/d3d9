#ifndef D3D9_FONT_H
#define D3D9_FONT_H

#include <string>
#include <d3dx9.h>
#include "device.hh"
#include "enums.hh"
#include <dxutil/comptr.hh>

namespace d3d9 {

struct Font {


private:
    DxUtil::ComPtr<ID3DXFont> font_;
};

}

#endif
