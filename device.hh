//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_D3DDEVICE_H
#define D3D9_D3DDEVICE_H

#include <d3d9.h>

#include "capabilities.h"
#include "comptr.h"
#include "direct3d.h"
#include "error.h"

namespace d3d9 {

struct Device {
    Device(const Direct3D &d3d, HWND hwnd, bool multithread = false)
        : hwnd_{hwnd} {
        D3DCAPS9 caps;
        HRESULT hr;
        if (FAILED(hr = d3d.get()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps))) {
            throw Exception(hr, "Failed to get device capabilities for default adapter.", D3D9_ERROR_LOCATION);
        }

        DWORD behaviour = multithread ? D3DCREATE_MULTITHREADED : 0;
        behaviour |= (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

        //TODO: Adapters
        createPP();
        if (FAILED(hr = d3d.get()->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, behaviour, &pp_, dev_.address()))) {
            throw Exception(hr, "Failed to create Direct3D9 device.", D3D9_ERROR_LOCATION);
        }

        enableDepth();
    }

    Device(IDirect3DDevice9 *iface)
        : dev_{iface} {
        enableDepth();
    }

    bool cooperative() const {
        HRESULT hr;
        if (FAILED(hr = dev_->TestCooperativeLevel())) {
            switch (hr) {
                case D3DERR_DEVICELOST: {
                    return false;
                }

                case D3DERR_DEVICENOTRESET: {
                    return true;
                }

                case D3DERR_DRIVERINTERNALERROR: {
                    throw Exception(hr, D3D9_ERROR_LOCATION);
                }
            }
        }

        return true;
    }

    void reset() {
        createPP();
        HRESULT hr;
        if (FAILED(hr = dev_->Reset(&pp_))) {
            throw Exception(hr, D3D9_ERROR_LOCATION);
        }
    }

    bool cullsCw() const {
        return getRenderState(D3DRS_CULLMODE) == D3DCULL_CW;
    }

    bool cullsCcw() const {
        return getRenderState(D3DRS_CULLMODE) == D3DCULL_CCW;
    }

    bool culls() const {
        return cullsCw() || cullsCcw();
    }

    void cullCw() const {
        setRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    }

    void cullCcw() const {
        setRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    }

    void disableCulling() const {
        setRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    }

    bool lights() const {
        return getRenderState(D3DRS_LIGHTING);
    }

    void lightsOn() const {
        setRenderState(D3DRS_LIGHTING, TRUE);
    }

    void lightsOff() const {
        setRenderState(D3DRS_LIGHTING, FALSE);
    }

    void toggleLights() const {
        lights() ? lightsOff() : lightsOn();
    }

    bool depth() const {
        return getRenderState(D3DRS_ZENABLE);
    }

    void enableDepth() const {
        setRenderState(D3DRS_ZENABLE, TRUE);
    }

    void disableDepth() const {
        setRenderState(D3DRS_ZENABLE, FALSE);
    }

    void toggleDepth() const {
        depth() ? disableDepth() : enableDepth();
    }

    IDirect3DDevice9 *get() const {
        return dev_.get();
    }

private:
    DxUtil::ComPtr<IDirect3DDevice9> dev_{};
    D3DPRESENT_PARAMETERS pp_;
    HWND hwnd_;

    void createPP() {
        ZeroMemory(&pp_, sizeof pp_);

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

    void setRenderState(D3DRENDERSTATETYPE type, DWORD value) const {
        HRESULT hr;
        if (FAILED(hr = dev_->SetRenderState(type, value))) {
            throw Exception(hr, D3D9_ERROR_LOCATION);
        }
    }

    DWORD getRenderState(D3DRENDERSTATETYPE type) const {
        DWORD ret;
        HRESULT hr;
        if (FAILED(hr = dev_->GetRenderState(type, &ret))) {
            throw Exception(hr, D3D9_ERROR_LOCATION);
        }

        return ret;
    }
};

}

#endif
