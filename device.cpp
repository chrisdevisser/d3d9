#include <d3d9.h>

#include "device.hh"
#include "direct3d.hh"
#include "enums.hh"
#include "error.hh"
#include <dxutil/comptr.hh>

namespace d3d9 {
inline namespace DeviceNs {

Device::Device(const Direct3D &d3d_, const HWND hwnd, const bool multithread)
    : hwnd_{hwnd} {
    D3DCAPS9 caps;
    HRESULT hr;
    if (FAILED(hr = d3d_.d3d()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps))) {
        throw Exception(hr, "Failed to get device capabilities for default adapter.", D3D9_ERROR_LOCATION);
    }

    DWORD behaviour = multithread ? D3DCREATE_MULTITHREADED : 0;
    behaviour |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    //TODO: Adapters
    createPP();
    if (FAILED(hr = d3d_.d3d()->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, behaviour, &pp_, dev_.address()))) {
        throw Exception(hr, "Failed to create Direct3D9 device.", D3D9_ERROR_LOCATION);
    }

    depth(true);
}

Device::Device(IDirect3DDevice9 * const iface) : dev_{iface} {depth(true);}

void Device::reset() {
    createPP();
    HRESULT hr;
    if (FAILED(hr = dev_->Reset(&pp_))) throw Exception(hr, D3D9_ERROR_LOCATION);
}

bool Device::cullsCw() const {return getRenderState(D3DRS_CULLMODE) == D3DCULL_CW;}
bool Device::cullsCcw() const {return getRenderState(D3DRS_CULLMODE) == D3DCULL_CCW;}
bool Device::culls() const {return cullsCw() || cullsCcw();}
void Device::cull(const Cull type) const {setRenderState(D3DRS_CULLMODE, static_cast<D3DCULL>(static_cast<int>(type)));}

bool Device::lights() const {return getRenderState(D3DRS_LIGHTING);}
void Device::lights(const bool on) const {setRenderState(D3DRS_LIGHTING, on);}

bool Device::depth() const {return getRenderState(D3DRS_ZENABLE);}
void Device::depth(const bool on) const {setRenderState(D3DRS_ZENABLE, on);}

IDirect3DDevice9 *Device::d3d() const {return dev_.get();}

void Device::createPP() noexcept {
    pp_ = {};

    DWORD style = GetWindowLongPtrW(hwnd_, GWL_STYLE);
    DWORD exStyle = GetWindowLongPtrW(hwnd_, GWL_EXSTYLE);
    bool fullscreen = (style & WS_POPUP) && (exStyle & WS_EX_TOPMOST);

    pp_.Windowed = !fullscreen;
    pp_.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp_.hDeviceWindow = hwnd_;
    pp_.BackBufferFormat = fullscreen ? D3DFMT_X8R8G8B8 : D3DFMT_UNKNOWN;
    pp_.BackBufferWidth = fullscreen ? GetSystemMetrics(SM_CXSCREEN) : 0;
    pp_.BackBufferHeight = fullscreen ? GetSystemMetrics(SM_CYSCREEN) : 0;
    pp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    pp_.EnableAutoDepthStencil = TRUE;
    pp_.AutoDepthStencilFormat = D3DFMT_D16;
}

void Device::setRenderState(const D3DRENDERSTATETYPE type, DWORD const value) const {
    HRESULT hr;
    if (FAILED(hr = dev_->SetRenderState(type, value))) throw Exception(hr, D3D9_ERROR_LOCATION);
}

DWORD Device::getRenderState(const D3DRENDERSTATETYPE type) const {
    DWORD ret;
    HRESULT hr;
    if (FAILED(hr = dev_->GetRenderState(type, &ret))) throw Exception(hr, D3D9_ERROR_LOCATION);
    return ret;
}

bool Cooperative(const Device &dev) {
    HRESULT hr;
    if (FAILED(hr = dev.d3d()->TestCooperativeLevel())) {
        switch (hr) {
            case D3DERR_DEVICELOST: return false;
            case D3DERR_DEVICENOTRESET: return true;

            case D3DERR_DRIVERINTERNALERROR:
            default:
                throw Exception(hr, D3D9_ERROR_LOCATION);
        }
    }

    return true;
}

}
}
