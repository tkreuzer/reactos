

typedef struct _DEVMODEINFO
{
    struct _DEVMODEINFO *pdmiNext;
    struct _LDEVOBJ *pldev;
    ULONG cbdevmode;
    DEVMODEW adevmode[1];
} DEVMODEINFO, *PDEVMODEINFO;

typedef struct _DEVMODEENTRY
{
    DWORD dwFlags;
    PDEVMODEW pdm;
} DEVMODEENTRY, *PDEVMODEENTRY;

class GRAPHICS_DEVICE
{
    WCHAR            szNtDeviceName[CCHDEVICENAME/2];
    WCHAR            szWinDeviceName[CCHDEVICENAME/2];
    GRAPHICS_DEVICE *pNextGraphicsDevice;
    GRAPHICS_DEVICE *pVgaDevice;
    PDEVICE_OBJECT   DeviceObject;
    PVOID            pDeviceHandle;
    DWORD            hkClassDriverConfig;
    DWORD            StateFlags;                     /* See DISPLAY_DEVICE_* */
    ULONG            cbdevmodeInfo;
    PDEVMODEINFO     pdevmodeInfo;
    ULONG            cDevModes;
    PDEVMODEENTRY    pDevModeList;
    LPWSTR           pDiplayDrivers;
    LPWSTR           pwszDescription;
    DWORD            dwMonCnt;
    PVIDEO_MONITOR_DEVICE pvMonDev;
    PFILE_OBJECT     FileObject;
    DWORD            ProtocolType;


    GRAPHICS_DEVICE();

    ~GRAPHICS_DEVICE();

    static
    VOID
    GRAPHICS_DEVICE::vFreeDevModeInfo (
        );



}

