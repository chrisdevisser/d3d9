#include <d3d9.h>
#include "colour.hh"

namespace d3d9 {
inline namespace ColourNs {

Colour::Colour(const unsigned char r_, const unsigned char g_, const unsigned char b_, const unsigned char a_) noexcept
    : r{r_}, g{g_}, b{b_}, a{a_} {}

Colour::Colour(const D3DCOLOR d3d_) noexcept
    : Colour((d3d_ >> 24) & 0xff, (d3d_ >> 16) & 0xff, (d3d_ >> 8) & 0xff, d3d_ & 0xff) {}

D3DCOLOR d3d(const Colour &col) noexcept {
    return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
}

const Colour Colours::Black  {  0,   0,   0};
const Colour Colours::Red    {255,   0,   0};
const Colour Colours::Yellow {255, 255,   0};
const Colour Colours::Green  {  0, 255,   0};
const Colour Colours::Cyan   {  0, 255, 255};
const Colour Colours::Blue   {  0,   0, 255};
const Colour Colours::Magenta{255,   0, 255};
const Colour Colours::White  {255, 255, 255};

}
}
