//Copyright Chris DeVisser 2013
//Code may be used freely in personal and commercial environments.
//Compiled with GCC 4.8.1 and MinGWBuilds - http://sourceforge.net/projects/mingwbuilds/

#ifndef D3D9_ENUMS_H
#define D3D9_ENUMS_H

#include "flags.h"

namespace d3d9 {

enum class PrimitiveType {
    PointList = 1,
    LineList,
    LineStrip,
    TriangleList,
    TriangleStrip,
    TriangleFan
};

enum class FontWeight {
    Default,
    Thin = 100,
    ExtraLight = 200,
    UltraLight = 200,
    Light = 300,
    Normal = 400,
    Regular = 400,
    Medium = 500,
    SemiBold = 600,
    DemiBold = 600,
    Bold = 700,
    ExtraBold = 800,
    UltraBold = 800,
    Heavy = 900,
    Black = 900
};

enum class Charset {
    Ansi = ANSI_CHARSET,
    Baltic = BALTIC_CHARSET,
    ChineseBig5 = CHINESEBIG5_CHARSET,
    Default = DEFAULT_CHARSET,
    EastEurope = EASTEUROPE_CHARSET,
    Gb2312 = GB2312_CHARSET,
    Greek = GREEK_CHARSET,
    Hangeul = HANGEUL_CHARSET,
    Mac = MAC_CHARSET,
    Oem = OEM_CHARSET,
    Russian = RUSSIAN_CHARSET,
    ShiftJis = SHIFTJIS_CHARSET,
    Symbol = SYMBOL_CHARSET,
    Turkish = TURKISH_CHARSET,
    Johab = JOHAB_CHARSET,
    Hebrew = HEBREW_CHARSET,
    Arabic = ARABIC_CHARSET,
    Thai = THAI_CHARSET
};

enum class OutputPrecision {
    Default = OUT_DEFAULT_PRECIS,
    Raster = OUT_RASTER_PRECIS,
    String = OUT_STRING_PRECIS
};

enum class Quality {
    AntiAliased = ANTIALIASED_QUALITY,
    NonAntiAliased = NONANTIALIASED_QUALITY,
    Default = DEFAULT_QUALITY,
    Draft = DRAFT_QUALITY
};

enum class Pitch {
    Default = DEFAULT_PITCH,
    Fixed = FIXED_PITCH,
    Variable = VARIABLE_PITCH
};

enum class Family {
    Decorative = FF_DECORATIVE,
    Default = FF_DONTCARE,
    Modern = FF_MODERN,
    Roman = FF_ROMAN,
    Script = FF_SCRIPT,
    Swiss = FF_SWISS
};

}

#endif
