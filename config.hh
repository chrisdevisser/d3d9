#ifndef D3D9_CONFIG_H
#define D3D9_CONFIG_H

//for the window icon and cursor
#ifndef OEMRESOURCE
    #define OEMRESOURCE
#endif

//because #undef causes errors and leaving it causes errors
#include <algorithm>
using std::max;
using std::min;

#endif
