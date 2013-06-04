This is just a fun thing to do while I learn D3D9. I'll try to evolve my skills with projects as I do and try to keep the resulting code easy to use, but easy enough to read.

Current features:
-default window that takes the entire usable screen, option for fullscreen, wraps user window procedure in its own
-would like to have the library's window procedure be easier to make use of with custom windows
-library wndproc handles resetting an invalid device via detail::Message::ResetDevice (WM_USER)
-would like to add things to library wndproc to keep track of keyboard and mouse input

-message loop or threaded message loop, latter runs supplied function in a new thread, which allows drawing while moving/sizing the window
-default option of using spare time to sleep for remaining time until next frame
-default FPS of 30, but can be any arithmetic value, and is reference, ergo changes as variable does

-initialization wrapped up
-optional multithreaded
-easy render state manipulation
-enum class versions of enums
-scene class ctor/dtor will clear and present
-vertex buffer wrapped with premade POD-with-constructor vertex types
-translation, rotation, scaling, projection, and perspective transformations wrapped

-exceptions as prime form of error handling
-contain error code, message, location


This project is very C++11-reliant. I'm glad to say I don't have to keep backward-compatibility with code that is years old, as it's all fresh. I plan on using C++14 as soon as possible.

This is mainly compiled with GCC. At the time of writing, I use the MinGWBuilds GCC 4.8.1, which has standard threading that works on Windows. I'm fairly pedantic with warnings, and I aim for a clean build with at least -Wall, -Wextra, and -pedantic.

This project relies on my stdx and dxutil libraries, which I started with this. stdx is for things that can be implemented without any non-standard headers, and dxutil is for DirectX utilities that I think will be used the same way for D3D9 as they will for D3D10, D3D11, DSound, DShow, etc.

As of now, the project does not rely on Boost. I won't hesitate too much to add Boost, but might get rid of dependencies on it if it's trivial to do so.