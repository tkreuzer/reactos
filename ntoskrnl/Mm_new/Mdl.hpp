/*!

    \file Mdl.hpp

    \brief Header for Mdl.cpp

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#pragma once

#include "ntosbase.h"

//typedef class CMDL *PCMDL;

class MDLX : _MDL
{
private:


public:

    static
    PMDL
    AllocateMdl (
        _In_opt_ PVOID VirtualAddress,
        _In_ ULONG Length,
        _In_ BOOLEAN SecondaryBuffer,
        _In_ BOOLEAN ChargeQuota,
        _Inout_opt_ PIRP Irp);

    inline
    VOID
    Initialize (
        _In_ PVOID BaseVa,
        _In_ SIZE_T Length);

    inline
    ULONG
    GetByteCount (
        VOID)
    {
        return 0;
    }

    inline
    ULONG
    GetByteOffset (
        VOID)
    {
        return 0;
    }

    inline
    PPFN_NUMBER
    GetPfnArray (
        VOID)
    {
        return 0;
    }

    NTSTATUS
    Advance (
        _In_ ULONG NumberOfBytes);



};
