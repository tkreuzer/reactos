/*
 * PROJECT:         ReactOS PCI Bus Driver
 * LICENSE:         BSD - See COPYING.ARM in the top level directory
 * FILE:            drivers/bus/pci/intrface/cardbus.c
 * PURPOSE:         CardBus Interface
 * PROGRAMMERS:     ReactOS Portable Systems Group
 */

/* INCLUDES *******************************************************************/

#include <pci.h>
#define NDEBUG
#include <debug.h>

/* GLOBALS ********************************************************************/

PCI_INTERFACE PciCardbusPrivateInterface =
{
    &GUID_PCI_CARDBUS_INTERFACE_PRIVATE,
    sizeof(PCI_CARDBUS_INTERFACE_PRIVATE),
    PCI_CB_INTRF_VERSION,
    PCI_CB_INTRF_VERSION,
    PCI_INTERFACE_PDO,
    0,
    PciInterface_PciCb,
    pcicbintrf_Constructor,
    pcicbintrf_Initializer
};

/* FUNCTIONS ******************************************************************/

NTSTATUS
NTAPI
pcicbintrf_Initializer(IN PVOID Instance)
{
    /* PnP Interfaces don't get Initialized */
    ASSERTMSG(FALSE, "PCI pcicbintrf_Initializer, unexpected call.");
    return STATUS_UNSUCCESSFUL;
}

NTSTATUS
NTAPI
pcicbintrf_Constructor(IN PVOID DeviceExtension,
                       IN PVOID Instance,
                       IN PVOID InterfaceData,
                       IN USHORT Version,
                       IN USHORT Size,
                       IN PINTERFACE Interface)
{
    /* Not yet implemented */
    UNIMPLEMENTED;
    while (TRUE);
}

/* EOF */