
#pragma once

#include "Rtl.hpp"

// winnt.h
typedef enum _ACL_INFORMATION_CLASS
{
    AclRevisionInformation = 1,
    AclSizeInformation
} ACL_INFORMATION_CLASS;

typedef struct _ACL
{
    UCHAR AclRevision;
    UCHAR Sbz1;
    USHORT AclSize;
    USHORT AceCount;
    USHORT Sbz2;
} ACL, *PACL;

typedef struct _ACE *PACE;

