
#include "DibLib.h"

#define __USES_SOURCE 0
#define __USES_PATTERN 1
#define __USES_DEST 1
#define __USES_MASK 0

#define PFN_DIBFUNCTION PFN_DIB_LINETO
#define __HEADER_NAME "DibLib_Line.h"
#define __FUNCTIONNAME Line_MajorX

#include "DibLib_AllDstBPP.h"

#undef __FUNCTIONNAME
#define __FUNCTIONNAME Line_MajorY
#define __INVERTED_COORDINATES 1
#include "DibLib_AllDstBPP.h"

