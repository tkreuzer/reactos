Coding Guidelines
===============================

[TOC]



Coding Style
---





Kernel APIs
---



Systemcall APIs
---

SyscallApi.hpp

```
#pragma once

...

#define KMPOBJECT_
```



NtXyApi.hpp

```c++
#pragma once

#include <NtTypes.h>

#ifndef __USE_NATIVE_UM_TYPES
#include <SyscallApi.h>
#endif

```



Example implementation:

```c++
#include <SyscallApi.hpp> ///< For UM pointer stuff
#include <NtXyApi.hpp> ///< This has all the things for all NtXy functions

NTSTATUS
NTAPI
NtDoSomeStuffWithPointersAndHandlesAndExtraSauceSuperSecure (
    _In_ HANDLE ObjectHandle,
    _In_ UMPCOBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ UMPHANDLE 
    )
{
    OBJECT_ATTRIBUTES localObjectAttributes;
    NTSTATUS status;

    try
    {
        /* First probe and copy object attributes at all levels */
        localObjectAttributes = ProbeAndDeepCopy(ObjectAttributes);

        status = XyDoSomeStuffWithPointersAndHandlesAndExtraSauceSuperSecure(ObjectHandle,
                                                                             ObjectAttributes,
                                                                             )
    }
    catch(EXCEPTION &exception)
    {
        status = exception.GetExceptionCode();
    }

    return status;
}

```

---