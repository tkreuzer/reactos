/*
 *  FreeLoader - registry.h
 *
 *  Copyright (C) 2001  Eric Kohl
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __REGISTRY_H
#define __REGISTRY_H

#define TAG_REG_NAME 'NgeR'
#define TAG_REG_KEY 'KgeR'
#define TAG_REG_KEY_DATA 'DgeR'
#define TAG_REG_VALUE 'VgeR'

BOOLEAN
RegImportBinaryHive(
    _In_ PVOID ChunkBase,
    _In_ ULONG ChunkSize);

typedef struct _REG_KEY
{
    LIST_ENTRY KeyList;
    LIST_ENTRY SubKeyList;
    LIST_ENTRY ValueList;

    ULONG SubKeyCount;
    ULONG ValueCount;

    ULONG NameSize;
    PWCHAR Name;

    /* Default data */
    ULONG DataType;
    ULONG DataSize;
    PCHAR Data;
} KEY, *FRLDRHKEY, **PFRLDRHKEY;


typedef struct _REG_VALUE
{
    LIST_ENTRY ValueList;

    /* Value name */
    ULONG NameSize;
    PWCHAR Name;

    /* Value data */
    ULONG DataType;
    ULONG DataSize;
    PCHAR Data;
} VALUE, *PVALUE;

VOID
RegInitializeRegistry(VOID);

LONG
RegInitCurrentControlSet(
    _In_ BOOLEAN LastKnownGood);

extern HKEY CurrentControlSetKey;

/*
 * LONG
 * RegCloseKey(
 *     _In_ HKEY hKey);
 */
#define RegCloseKey(hKey)   (ERROR_SUCCESS)

LONG
RegEnumKey(
    _In_ FRLDRHKEY Key,
    _In_ ULONG Index,
    _Out_ PWCHAR Name,
    _Inout_ PULONG NameSize,
    _Out_opt_ FRLDRHKEY *SubKey);

LONG
RegOpenKey(
    _In_ FRLDRHKEY ParentKey,
    _In_z_ PCWSTR KeyName,
    _Out_ PHKEY Key);

LONG
RegSetValue(FRLDRHKEY Key,
        PCWSTR ValueName,
        ULONG Type,
        PCSTR Data,
        ULONG DataSize);

LONG
RegQueryValue(
    _In_ FRLDRHKEY Key,
    _In_z_ PCWSTR ValueName,
    _Out_opt_ PULONG Type,
    _Out_opt_ PUCHAR Data,
    _Inout_opt_ PULONG DataSize);

LONG
RegDeleteValue(FRLDRHKEY Key,
           PCWSTR ValueName);

#if 0
LONG
RegEnumValue(
    _In_ FRLDRHKEY Key,
    _In_ ULONG Index,
    _Out_ PWCHAR ValueName,
    _Inout_ PULONG NameSize,
    _Out_opt_ PULONG Type,
    _Out_opt_ PUCHAR Data,
    _Inout_opt_ PULONG DataSize)
#endif

ULONG
RegGetSubKeyCount (FRLDRHKEY Key);

ULONG
RegGetValueCount (FRLDRHKEY Key);


BOOLEAN
RegImportBinaryHive (PCHAR ChunkBase,
             ULONG ChunkSize);

BOOLEAN
RegExportBinaryHive (PCWSTR KeyName,
             PCHAR ChunkBase,
             ULONG* ChunkSize);


#endif /* __REGISTRY_H */

/* EOF */
