
#pragma once

#include <ntoskrnl.h>

// vffailure.h
typedef enum
{
    VFFAILURE_FAIL_IN_FIELD = 0,
    VFFAILURE_FAIL_LOGO = 1,
    VFFAILURE_FAIL_UNDER_DEBUGGER = 2
} VF_FAILURE_CLASS, *PVF_FAILURE_CLASS;

// vffailure.h
typedef enum
{
    VFOBJTYPE_DRIVER = 0,
    VFOBJTYPE_DEVICE,
    VFOBJTYPE_SYSTEM_BIOS
} VF_OBJECT_TYPE;
