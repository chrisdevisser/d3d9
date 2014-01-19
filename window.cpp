#include <functional>

#include "window.hh"

namespace d3d9 {

namespace detail {
    extern "C" LRESULT CALLBACK ProxyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        const auto proc = static_cast<Window *>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
        if (proc) {proc->callWndProc(hwnd, msg, wParam, lParam);}

        switch (msg) {
            case Message::ResetDevice: {
                Device &dev = *reinterpret_cast<Device *>(lParam);
                if (Cooperative(dev)) {dev.reset();}
                break;
            }

            case WM_CLOSE: {
                CallWindowProcW(hwnd, msg, wParam, lParam);
                SetWindowLongPtrW(hwnd, GWLP_USERDATA, nullptr);
                proc = nullptr;
            }
        }

        if (!proc) {DefWindowProcW(hwnd, msg, wParam, lParam);}
    }
}

Window::Window(const detail::WrappedWndProcType &f = DefWindowProcW, bool fullscreen = false) {
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpfnWndProc = detail::ProxyWndProc;
    wc.lpszClassName = L"D3D9 Default Window Class";
    wc.hbrBackground = fullscreen ? nullptr : reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.hCursor = static_cast<HCURSOR>(LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
    wc.hIcon = static_cast<HICON>(LoadImageW(nullptr, MAKEINTRESOURCEW(OIC_SAMPLE), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

    if (!RegisterClassExW(&wc)) {
        throw Exception(-1, "Failed to register window class, with error " + std::to_string(GetLastError()) + ".", D3D9_ERROR_LOCATION);
    }

    int x = fullscreen ? 0 : CW_USEDEFAULT;
    int y = fullscreen ? 0 : CW_USEDEFAULT;
    int width = fullscreen ? GetSystemMetrics(SM_CXSCREEN) : CW_USEDEFAULT;
    int height = fullscreen ? GetSystemMetrics(SM_CYSCREEN) : CW_USEDEFAULT;
    DWORD exFlags = fullscreen ? WS_EX_TOPMOST : 0;
    DWORD flags = WS_VISIBLE | WS_MAXIMIZE;
    flags |= (fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW);

    HWND hwnd;
    if (!(hwnd = CreateWindowExW(exFlags, wc.lpszClassName, L"Direct3D9 Window", flags, x, y, width, height, nullptr, nullptr, GetModuleHandle(nullptr), new auto(f)))) {
        throw Exception(-1, "Failed to create window, with error " + std::to_string(GetLastError()) + ".", D3D9_ERROR_LOCATION);
    }

    return hwnd;
}

}

