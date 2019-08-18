#ifndef COMPAT_UNDOC_H
#define COMPAT_UNDOC_H


typedef struct _ReactOS_ShimData
{
    DWORD dwReserved1[130];
    DWORD dwSize;
    DWORD dwMagic;
    DWORD dwReserved2[242];
    DWORD dwRosProcessCompatVersion;
} ReactOS_ShimData;


#define REACTOS_SHIMDATA_MAGIC  0xAC0DEDAB

#ifndef WINVER_VISTA
#define WINVER_VISTA    0x0600
#define WINVER_WIN7     0x0601
#define WINVER_WIN8     0x0602
#define WINVER_WIN81    0x0603
#define WINVER_WIN10    0x0a00
#endif

DWORD
NTAPI
RosGetProcessCompatVersion(VOID);

#endif // COMPAT_UNDOC_H
