//Represents IDirect3DDevice9.

#ifndef D3D9_D3DDEVICE_H
#define D3D9_D3DDEVICE_H

#include <d3d9.h>
#include <dxutil/comptr.hh>

namespace d3d9 {

enum class Cull;
class Direct3D;

inline namespace DeviceNs {

struct Device {
    Device(const Direct3D &d3d, HWND hwnd, bool multithread = false);
    Device(IDirect3DDevice9 *iface);

    void reset();

    bool cullsCw() const;
    bool cullsCcw() const;
    bool culls() const;
    void cull(Cull type) const;

    bool lights() const;
    void lights(bool on) const;

    bool depth() const;
    void depth(bool on) const;

    IDirect3DDevice9 *d3d() const;

private:
    DxUtil::ComPtr<IDirect3DDevice9> dev_;
    D3DPRESENT_PARAMETERS pp_;
    HWND hwnd_;

    void createPP() noexcept;
    void setRenderState(D3DRENDERSTATETYPE type, DWORD value) const;
    DWORD getRenderState(D3DRENDERSTATETYPE type) const;
};

bool Cooperative(const Device &dev);

}
}

#endif
