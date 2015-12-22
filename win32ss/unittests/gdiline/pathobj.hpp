
#pragma once

class EPATHOBJ : public _PATHOBJ
{
    struct _PATH *_ppath;
    CLIPOBJ *_pco;
    PATHDATA _pdEnum;
    struct
    {
        BOOL _bMorePaths : 1;
        BOOL _bMoreClips : 1;
    };

public:

    EPATHOBJ(
        VOID);

    ~EPATHOBJ(
        VOID);

    BOOL
    bAllocatePath(
        VOID);

    VOID
    vEnumStart(
        VOID);

    BOOL
    bEnum(
        _Out_ PATHDATA *ppd);

    VOID
    vEnumStartClipLines(
        _Inout_ CLIPOBJ *pco,
        _In_ SURFOBJ *pso,
        _In_ LINEATTRS *pla);

    BOOL
    bEnumClipLines(
        _Inout_ PATHOBJ *ppo,
        _In_ ULONG cj,
        _Out_ CLIPLINE *pcl);

};
