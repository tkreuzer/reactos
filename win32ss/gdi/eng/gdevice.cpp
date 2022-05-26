


/*

TODO:
 + Implement GRAPHICS_DEVICE here!
 * First implement c++ LDEV!
 * Check if hpoussin changed structure definitions
 * A GRAPHICS_DEVICE will be constructed for every physical display device in the system
 * it does not necessarily have a PDEV associated with it

Affected file list:
   - win32ss/gdi/eng/device.c
        - EngpUpdateGraphicsDeviceList -> calls InitDisplayDriver
            - Move this to USER
            - 
   - win32ss/gdi/eng/device.h
   - win32ss/gdi/eng/ldevobj.c
   - win32ss/gdi/eng/ldevobj.h
   - win32ss/gdi/eng/mdevobj.c -> probably OK
   - win32ss/gdi/eng/pdevobj.c - probably OK
   - win32ss/gdi/eng/pdevobj.h -> this contains the structure, should include gdevice.hpp
   - win32ss/reactx/ntddraw/dxeng.c -> only a comment
   - win32ss/user/ntuser/display.c -> OOF!
        - InitDisplayDriver()
            - uses EngpRegisterGraphicsDevice, which can be changed to return BOOL
            - uses pGraphicsDevice->StateFlags -> move that to EngpRegisterGraphicsDevice
            - returns a pointer to it, used by EngpUpdateGraphicsDeviceList
                -> 
        - UserEnumDisplayDevices
            - Doesn't have a reference on pGraphicsDevice!
            --> call UpdateGraphicsDeviceList(&v7); + DrvEnumDisplayDevices
        - UserEnumDisplaySettings
            - call DrvEnumDisplaySettings
   - win32ss/user/ntuser/ntuser.h -> OOF
   - win32ss/user/ntuser/winsta.c -> contains only the display hack, move this to HackDisplayDevices()


    1. Clean up USER
        - Move pGraphicsDevice->StateFlags handling from InitDisplayDriver to EngpRegisterGraphicsDevice
        - Move pGraphicsDevice->StateFlags handling from EngpUpdateGraphicsDeviceList to EngpRegisterGraphicsDevice
        - Move handling of existing driver from EngpUpdateGraphicsDeviceList to EngpRegisterGraphicsDevice
        - return BOOL from EngpRegisterGraphicsDevice and InitDisplayDriver
        - Rename EngpUpdateGraphicsDeviceList to UserUpdateGraphicsDeviceList and move to ntuser/display.c

    ?. Handle device cleanup


 Other:

 "[WIN32SS] Implement LDEVOBJ_ulGetDriverModes"
 * Replaces LDEVOBJ_pdmiGetModes
 * LDEVOBJ_ulGetModes Function loads the driver first, which is stupid
 * LDEVOBJ_ulGetModes donly returns the DEVMODE array, not the header!
 ** Now EngpPopulateDeviceModeList has to do an extra copy for the DEVMODEINFO
 * pdm is leaked
 -> revert!

 "[WIN32SS] Extract devmode list query to new function LDEVOBJ_bBuildDevmodeList"
 * LDEVOBJ_bBuildDevmodeList should be GRAPHICS_DEVICE::bBuildDevmodeList (rewite it to use LDEVOBJ_pdmiGetModes!)
 * Hierachy is PDEVOBJ -> GRAPHICS_DEVICE -> LDEVOBJ not the other way!



 "[WIN32K] Move detection of available display devices a new fonction EngpUpdateGraphicsDeviceList"
 * EngpUpdateGraphicsDeviceList calls InitDisplayDriver in USER
 * Should be moved to USER



*/

#include <gdevice.hpp>

// Constructor

GRAPHICS_DEVICE::GRAPHICS_DEVICE()
{

}

// Destructor
GRAPHICS_DEVICE:~GRAPHICS_DEVICE()
{
    // Must not be in the device list!
    ASSERT(pNextGraphicsDevice == NULL);

    // dereference DeviceObject;
    // close pDeviceHandle;
    // DWORD            hkClassDriverConfig;

    // free pDevModeList;

    //ULONG            cbdevmodeInfo;
    //PDEVMODEINFO     pdevmodeInfo;


    LPWSTR           pDiplayDrivers;
    LPWSTR           pwszDescription;
    DWORD            dwMonCnt;
    PVIDEO_MONITOR_DEVICE pvMonDev;
    PFILE_OBJECT     FileObject;
    DWORD            ProtocolType;
}

VOID
GRAPHICS_DEVICE::vFreeDevModeInfo (
    )
{
    // Dereference pldev

}
