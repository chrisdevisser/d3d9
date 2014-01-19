#ifndef D3D9_ERROR_H
#define D3D9_ERROR_H

#include <iosfwd>
#include <stdexcept>
#include <string>

#define D3D9_ERROR_LOCATION __FILE__, __func__, __LINE__

namespace d3d9 {
inline namespace ErrorNs {

inline std::string ErrorCodeToString(LONG);
inline std::string ErrorCodeToDescription(LONG);

struct Exception : std::runtime_error {
    Exception(LONG _code, const std::string &_info = {}) noexcept;
    Exception(LONG _code, const std::string &_file, const std::string &_func, int _line) noexcept;
    Exception(LONG _code, const std::string &_info, const std::string &_file, const std::string &_func, int _line) noexcept;

    LONG code() const noexcept;
    std::string info() const noexcept;
    std::string file() const noexcept;
    std::string function() const noexcept;
    int line() const noexcept;

private:
    LONG code_;
    std::string info_;
    std::string file_;
    std::string function_;
    int line_;
};

std::ostream &operator<<(std::ostream &out, const Exception &ex);

}
}

#endif
