//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_WINDOW_H
#define D3D9_WINDOW_H

#include <chrono>
#include <functional>
#include <stdexcept>
#include <windows.h>

#include "device.h"
#include "error.h"

namespace d3d9 {

namespace detail {
    namespace Message {
        enum : UINT {
            ResetDevice = WM_USER //LPARAM = Device *
        };
    }

    std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> WndProc;

    inline LRESULT CALLBACK DefWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (msg == Message::ResetDevice) {
            Device &dev = *reinterpret_cast<Device *>(lParam);
            if (dev.cooperative()) {
                dev.reset();
            }
        }

        return WndProc(hwnd, msg, wParam, lParam);
    }
}

template<typename F>
HWND CreateDefaultWindow(F f = DefWindowProcW, bool fullscreen = false) {
    detail::WndProc = f;

    WNDCLASSEXW wc;
    ZeroMemory(&wc, sizeof wc);
    wc.cbSize = sizeof wc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpfnWndProc = detail::DefWndProc;
    wc.lpszClassName = L"D3D9 Default Window Class";
    wc.hbrBackground = fullscreen ? nullptr : reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.hCursor = static_cast<HCURSOR>(LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
    wc.hIcon = static_cast<HICON>(LoadImageW(nullptr, MAKEINTRESOURCEW(OIC_SAMPLE), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

    RegisterClassExW(&wc);

    int x = fullscreen ? 0 : CW_USEDEFAULT;
    int y = fullscreen ? 0 : CW_USEDEFAULT;
    int width = fullscreen ? GetSystemMetrics(SM_CXSCREEN) : CW_USEDEFAULT;
    int height = fullscreen ? GetSystemMetrics(SM_CYSCREEN) : CW_USEDEFAULT;
    DWORD exFlags = fullscreen ? WS_EX_TOPMOST : 0;
    DWORD flags = WS_VISIBLE | WS_MAXIMIZE;
    flags |= (fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW);

    HWND hwnd;
    if (!(hwnd = CreateWindowExW(exFlags, L"D3D9 Default Window Class", L"Direct3D9 Window", flags, x, y, width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr))) {
        throw Exception(-1, "Failed to create window, with error " + std::to_string(GetLastError()) + ".", D3D9_ERROR_LOCATION);
    }

    return hwnd;
}

enum class MessageLoopOptions {
    Sleep,
    MaxCpu
};

template<typename Interval = std::chrono::milliseconds, typename F, typename Fps = int>
WPARAM MessageLoop(F f, const Fps &fps = 30, MessageLoopOptions opt = MessageLoopOptions::Sleep) {
    static_assert(std::is_arithmetic<Fps>::value, "FPS must be a number.");
    auto now = []{return std::chrono::steady_clock::now();};

    MSG msg;
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        thread_local auto last = now();
        double passed = std::chrono::duration_cast<Interval>(now() - last).count();

        if (passed >= Interval::period::den * 1. / fps) {
            f(passed);
            last = now();
        } else if (opt == MessageLoopOptions::Sleep) {
            Sleep(Interval::period::den * 1. / fps - passed);
        }
    }

    return 0;
}

namespace detail {
    std::function<void(double)> GameLoopThreadProc;

    //TODO: Replace with std::tuple<MessageLoopOptions, const Fps &>
    template<typename Fps>
    struct DefGameLoopThreadProcData {
        DefGameLoopThreadProcData(MessageLoopOptions opt_, const Fps &fps_)
            : options{opt_}, fps{fps_} {}

        MessageLoopOptions options;
        const Fps &fps;
    };

    template<typename Interval, typename Fps>
    DWORD WINAPI DefGameLoopThreadProc(LPVOID dataParam) {
        auto &data = *static_cast<DefGameLoopThreadProcData<Fps> *>(dataParam);
        auto now = []{return std::chrono::steady_clock::now();};

        while (true) {
            auto last = now();
            double passed = std::chrono::duration_cast<Interval>(now() - last).count();

            if (passed >= Interval::period::den * 1. / data.fps) {
                GameLoopThreadProc(passed);
                last = now();
            } else if (data.options == MessageLoopOptions::Sleep) {
                Sleep(Interval::period::den * 1. / data.fps - passed);
            }
        }

        return 0;
    }
}

template<typename Interval = std::chrono::milliseconds, typename F, typename Fps = int>
WPARAM ThreadedMessageLoop(F f, const Fps &fps = 30, MessageLoopOptions opt = MessageLoopOptions::Sleep) {
    static_assert(std::is_arithmetic<Fps>::value, "FPS must be a number.");

    detail::GameLoopThreadProc = f;
    detail::DefGameLoopThreadProcData<Fps> data{opt, fps};
    CreateThread(nullptr, 0, detail::DefGameLoopThreadProc<Interval, Fps>, &data, 0, nullptr); //TODO change with GCC thread support

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

}

#endif
