/* Automatically generated file; DO NOT EDIT!! */

#define STANDALONE
#include <wine/test.h>

extern void func_brush(void);
extern void func_customlinecap(void);
extern void func_font(void);
extern void func_graphics(void);
extern void func_graphicspath(void);
extern void func_image(void);
extern void func_matrix(void);
extern void func_metafile(void);
extern void func_pathiterator(void);
extern void func_pen(void);
extern void func_region(void);
extern void func_stringformat(void);

const struct test winetest_testlist[] =
{
    { "brush", func_brush },
    { "customlinecap", func_customlinecap },
    { "font", func_font },
#ifndef _M_AMD64 // region leak
    { "graphics", func_graphics },
#endif
#ifndef _M_AMD64 // crashes rosautotest?
    { "graphicspath", func_graphicspath },
#endif
#ifndef _M_AMD64 // UM exception
    { "image", func_image },
#endif
    { "matrix", func_matrix },
    { "metafile", func_metafile },
    { "pathiterator", func_pathiterator },
    { "pen", func_pen },
#ifndef _M_AMD64 // region leak
    { "region", func_region },
#endif
#ifndef _M_AMD64 // UM exception
    { "stringformat", func_stringformat },
#endif
    { 0, 0 }
};
