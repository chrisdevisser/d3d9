//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

//Provides an easier way to make colours and convert them to D3D.

#ifndef D3D9_COLOUR_H
#define D3D9_COLOUR_H

#include <d3d9.h>

namespace d3d9 {

struct Colour {
    constexpr Colour(unsigned char a_, unsigned char r_, unsigned char g_, unsigned char b_)
        : a{a_}, r{r_}, g{g_}, b{b_} {}

    constexpr Colour(unsigned char r_, unsigned char g_, unsigned char b_)
        : Colour{255, r_, g_, b_} {}

    constexpr Colour(D3DCOLOR d3d_)
        : Colour((d3d_ >> 24) & 0xff, (d3d_ >> 16) & 0xff, (d3d_ >> 8) & 0xff, d3d_ & 0xff) {}

    D3DCOLOR d3d() const {
        return D3DCOLOR_ARGB(a, r, g, b);
    }

    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Colours {
    static constexpr Colour Black   = {  0,   0,   0};
    static constexpr Colour Red     = {255, 255,   0};
    static constexpr Colour Yellow  = {255, 255,   0};
    static constexpr Colour Green   = {  0, 255,   0};
    static constexpr Colour Cyan    = {  0, 255, 255};
    static constexpr Colour Blue    = {  0,   0, 255};
    static constexpr Colour Magenta = {255,   0, 255};
    static constexpr Colour White   = {255, 255, 255};
};

}

#endif
