#ifndef D3D9_ENUMS_H
#define D3D9_ENUMS_H

//Mimics D3D9 enums with strong typing.

namespace d3d9 {

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

enum class Cull {
    None = D3DCULL_NONE,
    Cw = D3DCULL_CW,
    Ccw = D3DCULL_CCW
};

enum class Family {
    Decorative = FF_DECORATIVE,
    Default = FF_DONTCARE,
    Modern = FF_MODERN,
    Roman = FF_ROMAN,
    Script = FF_SCRIPT,
    Swiss = FF_SWISS
};

enum class FontWeight {
    Default = FW_DONTCARE,
    Thin = FW_THIN,
    ExtraLight = FW_EXTRALIGHT,
    UltraLight = FW_ULTRALIGHT,
    Light = FW_LIGHT,
    Normal = FW_NORMAL,
    Regular = FW_REGULAR,
    Medium = FW_MEDIUM,
    SemiBold = FW_SEMIBOLD,
    DemiBold = FW_DEMIBOLD,
    Bold = FW_BOLD,
    ExtraBold = FW_EXTRABOLD,
    UltraBold = FW_ULTRABOLD,
    Heavy = FW_HEAVY,
    Black = FW_BLACK
};

enum class OutputPrecision {
    Default = OUT_DEFAULT_PRECIS,
    Raster = OUT_RASTER_PRECIS,
    String = OUT_STRING_PRECIS
};

enum class Pitch {
    Default = DEFAULT_PITCH,
    Fixed = FIXED_PITCH,
    Variable = VARIABLE_PITCH
};

enum class PrimitiveType {
    PointList = D3DPT_POINTLIST,
    LineList = D3DPT_LINELIST,
    LineStrip = D3DPT_LINESTRIP,
    TriangleList = D3DPT_TRIANGLELIST,
    TriangleStrip = D3DPT_TRIANGLESTRIP,
    TriangleFan = D3DPT_TRIANGLEFAN
};

enum class Quality {
    AntiAliased = ANTIALIASED_QUALITY,
    NonAntiAliased = NONANTIALIASED_QUALITY,
    Default = DEFAULT_QUALITY,
    Draft = DRAFT_QUALITY
};

enum class TransformStateType {
    World = D3DTS_WORLD,
    View = D3DTS_VIEW,
    Projection = D3DTS_PROJECTION,
    Texture0 = D3DTS_TEXTURE0,
    Texture1 = D3DTS_TEXTURE1,
    Texture2 = D3DTS_TEXTURE2,
    Texture3 = D3DTS_TEXTURE3,
    Texture4 = D3DTS_TEXTURE4,
    Texture5 = D3DTS_TEXTURE5,
    Texture6 = D3DTS_TEXTURE6,
    Texture7 = D3DTS_TEXTURE7,
};

}

#endif
