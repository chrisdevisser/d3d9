#ifndef D3D9_ERROR_H
#define D3D9_ERROR_H

#include <exception>
#include <map>
#include <string>
#include <utility>
#include <d3d9.h>

#define D3D9_ERROR_LOCATION __FILE__, __func__, __LINE__

namespace d3d9 {

inline std::string ErrorCodeToString(LONG);
inline std::string ErrorCodeToDescription(LONG);

namespace detail {
    inline bool have(LONG);
}

struct Exception : std::exception {
    Exception(LONG c, const std::string i = {})
        : Exception(c, i, {}, {}, {}) {}

    Exception(LONG c, const std::string &f, const std::string &func, int l)
        : Exception(c, {}, f, func, l) {}

    Exception(LONG c, const std::string &i, const std::string &f, const std::string &func, int l)
        : code_{c}, info_{i}, file_{f}, function_{func}, line_{l} {}

    virtual const char *what() const noexcept override {
        return (
            ((detail::have(code_)) ? (ErrorCodeToString(code()) + " - " + ErrorCodeToDescription(code()) + '\n')
                : (code_ == -1 ? "" : "Error code: " + std::to_string(code_) + '\n'))
            + (file().empty() ? "" : ("File: " + file() + '\n'))
            + (function().empty() ? "" : ("Function: " + function() + '\n'))
            + (!line() ? "" : ("Line: " + std::to_string(line()) + '\n'))
            + (info().empty() ? "" : ("Extra info: " + info() + '\n'))
        ).c_str();
    }

    LONG code() const {
        return code_;
    }

    std::string info() const {
        return info_;
    }

    std::string file() const {
        return file_;
    }

    std::string function() const {
        return function_;
    }

    int line() const {
        return line_;
    }

private:
    LONG code_;
    std::string info_;
    std::string file_;
    std::string function_;
    int line_;
};

static const std::map<LONG, std::pair<std::string, std::string>> Code_StringAndDescription = {
    {D3DOK_NOAUTOGEN, {"D3DOK_NOAUTOGEN", "This is a success code. However, the autogeneration of mipmaps is not supported for this format. This means that resource creation will succeed but the mipmap levels will not be automatically generated."}},
    {D3DERR_CONFLICTINGRENDERSTATE, {"D3DERR_CONFLICTINGRENDERSTATE", "The currently set render states cannot be used together."}},
    {D3DERR_CONFLICTINGTEXTUREFILTER, {"D3DERR_CONFLICTINGTEXTUREFILTER", "The current texture filters cannot be used together."}},
    {D3DERR_CONFLICTINGTEXTUREPALETTE, {"D3DERR_CONFLICTINGTEXTUREPALETTE", "The current textures cannot be used simultaneously."}},
    {D3DERR_DEVICELOST, {"D3DERR_DEVICELOST", "The device has been lost but cannot be reset at this time. Therefore, rendering is not possible.A Direct 3D device object other than the one that returned this code caused the hardware adapter to be reset by the OS. Delete all video memory objects (surfaces, textures, state blocks) and call Reset() to return the device to a default state. If the application continues rendering without a reset, the rendering calls will succeed."}},
    {D3DERR_DEVICENOTRESET, {"D3DERR_DEVICENOTRESET", "The device has been lost but can be reset at this time."}},
    {D3DERR_DRIVERINTERNALERROR, {"D3DERR_DRIVERINTERNALERROR", "Internal driver error. Applications should destroy and recreate the device when receiving this error. For hints on debugging this error, see Driver Internal Errors (Direct3D 9)."}},
    {D3DERR_DRIVERINVALIDCALL, {"D3DERR_DRIVERINVALIDCALL", "Not used."}},
    {D3DERR_INVALIDCALL, {"D3DERR_INVALIDCALL", "The method call is invalid. For example, a method's parameter may not be a valid pointer."}},
    {D3DERR_INVALIDDEVICE, {"D3DERR_INVALIDDEVICE", "The requested device type is not valid."}},
    {D3DERR_MOREDATA, {"D3DERR_MOREDATA", "There is more data available than the specified buffer size can hold."}},
    {D3DERR_NOTAVAILABLE, {"D3DERR_NOTAVAILABLE", "This device does not support the queried technique."}},
    {D3DERR_NOTFOUND, {"D3DERR_NOTFOUND", "The requested item was not found."}},
    {D3D_OK, {"D3D_OK", "No error occurred."}},
    {D3DERR_OUTOFVIDEOMEMORY, {"D3DERR_OUTOFVIDEOMEMORY", "Direct3D does not have enough display memory to perform the operation. The device is using more resources in a single scene than can fit simultaneously into video memory. Present, PresentEx, or CheckDeviceState can return this error. Recovery is similar to D3DERR_DEVICEHUNG, though the application may want to reduce its per-frame memory usage as well to avoid having the error recur."}},
    {D3DERR_TOOMANYOPERATIONS, {"D3DERR_TOOMANYOPERATIONS", "The application is requesting more texture-filtering operations than the device supports."}},
    {D3DERR_UNSUPPORTEDALPHAARG, {"D3DERR_UNSUPPORTEDALPHAARG", "The device does not support a specified texture-blending argument for the alpha channel."}},
    {D3DERR_UNSUPPORTEDALPHAOPERATION, {"D3DERR_UNSUPPORTEDALPHAOPERATION", "The device does not support a specified texture-blending operation for the alpha channel."}},
    {D3DERR_UNSUPPORTEDCOLORARG, {"D3DERR_UNSUPPORTEDCOLORARG", "The device does not support a specified texture-blending argument for color values."}},
    {D3DERR_UNSUPPORTEDCOLOROPERATION, {"D3DERR_UNSUPPORTEDCOLOROPERATION", "The device does not support a specified texture-blending operation for color values."}},
    {D3DERR_UNSUPPORTEDFACTORVALUE, {"D3DERR_UNSUPPORTEDFACTORVALUE", "The device does not support the specified texture factor value. Not used; provided only to support older drivers."}},
    {D3DERR_UNSUPPORTEDTEXTUREFILTER, {"D3DERR_UNSUPPORTEDTEXTUREFILTER", "The device does not support the specified texture filter."}},
    {D3DERR_WASSTILLDRAWING, {"D3DERR_WASSTILLDRAWING", "The previous blit operation that is transferring information to or from this surface is incomplete."}},
    {D3DERR_WRONGTEXTUREFORMAT, {"D3DERR_WRONGTEXTUREFORMAT", "The pixel format of the texture surface is not valid."}},
    {E_FAIL, {"E_FAIL", "An undetermined error occurred inside the Direct3D subsystem."}},
    {E_INVALIDARG, {"E_INVALIDARG", "An invalid parameter was passed to the returning function."}},
    {E_NOINTERFACE, {"E_NOINTERFACE", "No object interface is available."}},
    {E_NOTIMPL, {"E_NOTIMPL", "Not implemented."}},
    {E_OUTOFMEMORY, {"E_OUTOFMEMORY", "Direct3D could not allocate sufficient memory to complete the call."}},
    {S_OK, {"S_OK", "No error occurred."}},
};

std::string ErrorCodeToString(LONG code) {
    return Code_StringAndDescription.at(code).first;
}

std::string ErrorCodeToDescription(LONG code) {
    return Code_StringAndDescription.at(code).second;
}

namespace detail {
    bool have(LONG code) {
        return Code_StringAndDescription.find(code) != std::end(Code_StringAndDescription);
    }
}

}

#endif
