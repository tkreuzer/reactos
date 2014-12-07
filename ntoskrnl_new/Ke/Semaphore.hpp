
#pragma once

#include "Kep.hpp"

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _SEMAPHORE_INFORMATION_CLASS
{
    SemaphoreBasicInformation = 0
} SEMAPHORE_INFORMATION_CLASS;

typedef struct _KSEMAPHORE *PKSEMAPHORE, *PRKSEMAPHORE;
