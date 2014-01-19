#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <d3d9.h>

#include "error.hh"

namespace d3d9 {
inline namespace ErrorNs {

static inline bool have(LONG code);

Exception::Exception(const LONG _code, const std::string &_info) noexcept : Exception(_code, _info, {}, {}, {}) {}
Exception::Exception(const LONG _code, const std::string &_file, const std::string &_func, const int _line) noexcept : Exception(_code, {}, _file, _func, _line) {}
Exception::Exception(const LONG _code, const std::string &_info, const std::string &_file, const std::string &_func, const int _line) noexcept
    : std::runtime_error{"A D3D9 exception has occurred. Use operator<< for a detailed output."}, code_{_code}, info_{_info}, file_{_file}, function_{_func}, line_{_line} {}

LONG Exception::code() const noexcept {return code_;}
std::string Exception::info() const noexcept {return info_;}
std::string Exception::file() const noexcept {return file_;}
std::string Exception::function() const noexcept {return function_;}
int Exception::line() const noexcept {return line_;}

std::ostream &operator<<(std::ostream &out, const Exception &ex) {
    if (have(ex.code())) out << ErrorCodeToString(ex.code()) << " - " << ErrorCodeToDescription(ex.code()) << "\n";
    else out << (ex.code() == -1 ? "" : "Error code: ") << ex.code() << "\n";

    if (!ex.file().empty()) out << "File: " << ex.file() << "\n";
    if (!ex.function().empty()) out << "Function: " << ex.function() << "\n";
    if (ex.line()) out << "Line: " << ex.line() << "\n";
    if (!ex.info().empty()) out << "Extra info: " << ex.info() << "\n";

    return out;
}

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

std::string ErrorCodeToString(const LONG code) {return Code_StringAndDescription.at(code).first;}
std::string ErrorCodeToDescription(const LONG code) {return Code_StringAndDescription.at(code).second;}

bool have(const LONG code) {
    return Code_StringAndDescription.find(code) != std::end(Code_StringAndDescription);
}

}
}

