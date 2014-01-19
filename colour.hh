//Provides an easier way to make colours and convert them to D3D. [0, 256)

#ifndef D3D9_COLOUR_H
#define D3D9_COLOUR_H

#include <d3d9.h>

namespace d3d9 {
inline namespace ColourNs {

typedef struct Colour {
    Colour(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255) noexcept;
    Colour(D3DCOLOR d3d_) noexcept;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

D3DCOLOR d3d(const Colour &col) noexcept;

typedef struct Colours {
    static const Colour Black;
    static const Colour Red;
    static const Colour Yellow;
    static const Colour Green;
    static const Colour Cyan;
    static const Colour Blue;
    static const Colour Magenta;
    static const Colour White;
} Colors;

}
namespace ColorNs = ColourNs;
}

#endif
