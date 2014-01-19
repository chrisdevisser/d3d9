#ifndef D3D9_WINDOW_H
#define D3D9_WINDOW_H

#include "config.hh"

#include <chrono>
#include <functional>
#include <stdexcept>
#include <thread>
#include <windows.h>

#include "device.hh"
#include "error.hh"

namespace d3d9 {

namespace Message {
    enum : UINT {
        ResetDevice = WM_USER, //LPARAM = Device *
    };
}

namespace detail {
    extern "C" LRESULT CALLBACK ProxyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

struct Window {
    Window(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> &wndProc, const bool fullscreen = false);
    ~Window() noexcept;
    operator HWND() const noexcept;
    callWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) const;

private:
    HWND hwnd_;
    const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> wndProc_;
};

enum class MessageLoopOptions {
    Sleep,
    MaxCpu
};

namespace detail {
    template<typename Interval, typename F, typename Fps>
    void CallTimedGameLoopFunction(const F f, const Fps fps, const MessageLoopOptions opt) {
        const auto now = []{return std::chrono::steady_clock::now();};
        thread_local auto last = now();
        const double passed = std::chrono::duration_cast<Interval>(now() - last).count();

        if (passed >= Interval::period::den * 1. / fps) {
            f(passed);
            last = now();
        } else if (opt == MessageLoopOptions::Sleep) {
            Sleep(Interval::period::den * 1. / fps - passed);
        }
    }
}

template<typename Interval = std::chrono::milliseconds, typename F, typename Fps>
WPARAM MessageLoop(const F f, const Fps &fps = 30, const MessageLoopOptions opt = MessageLoopOptions::Sleep) {
    static_assert(std::is_arithmetic<Fps>::value, "FPS must be a number.");

    MSG msg;
    for (;;) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        detail::CallTimedGameLoopFunction<Interval>(f, fps, opt);
    }

    return 0;
}

template<typename Interval = std::chrono::milliseconds, typename F, typename Fps>
WPARAM ThreadedMessageLoop(const F f, const Fps &fps = 30, const MessageLoopOptions opt = MessageLoopOptions::Sleep) {
    static_assert(std::is_arithmetic<Fps>::value, "FPS must be a number.");

    //create game loop thread
    std::thread{[=, &fps] {
        for (;;) {
            detail::CallTimedGameLoopFunction<Interval>(f, fps, opt);
        }
    }}.detach();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

}

#endif
