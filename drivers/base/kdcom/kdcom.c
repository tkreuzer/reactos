/*
 * COPYRIGHT:       GPL, see COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            drivers/base/kddll/kdcom.c
 * PURPOSE:         COM port functions for the kernel debugger.
 * PROGRAMMER:      Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include "kddll.h"

#include <cportlib/cportlib.h>
#include <arc/arc.h>
#include <stdio.h>
#include <stdlib.h>
#include <ndk/halfuncs.h>

/* Serial debug connection */
#if defined(SARCH_PC98)
#define DEFAULT_DEBUG_PORT      2 /* COM2 */
#define DEFAULT_DEBUG_COM1_IRQ  4
#define DEFAULT_DEBUG_COM2_IRQ  5
#define DEFAULT_DEBUG_BAUD_RATE 9600
#define DEFAULT_BAUD_RATE       9600
#else
#define DEFAULT_DEBUG_PORT      2 /* COM2 */
#define DEFAULT_DEBUG_COM1_IRQ  4
#define DEFAULT_DEBUG_COM2_IRQ  3
#define DEFAULT_DEBUG_BAUD_RATE 115200
#define DEFAULT_BAUD_RATE       19200
#endif

#define LSR_OE   0x02
#define LSR_PE   0x04
#define LSR_FE   0x08

#if defined(_M_IX86) || defined(_M_AMD64)
#if defined(SARCH_PC98)
const ULONG BaseArray[] = {0, 0x30, 0x238};
#else
const ULONG BaseArray[] = {0, 0x3F8, 0x2F8, 0x3E8, 0x2E8};
#endif
#elif defined(_M_PPC)
const ULONG BaseArray[] = {0, 0x800003F8};
#elif defined(_M_MIPS)
const ULONG BaseArray[] = {0, 0x80006000, 0x80007000};
#elif defined(_M_ARM)
const ULONG BaseArray[] = {0, 0xF1012000};
#else
#error Unknown architecture
#endif

#define MAX_COM_PORTS   (sizeof(BaseArray) / sizeof(BaseArray[0]) - 1)

/* GLOBALS ********************************************************************/

CPPORT KdComPort;
ULONG  KdComPortIrq = 0; // Not used at the moment.
#ifdef KDDEBUG
CPPORT KdDebugComPort;
#endif

/* DEBUGGING ******************************************************************/

#ifdef KDDEBUG
ULONG KdpDbgPrint(const char *Format, ...)
{
    va_list ap;
    int Length;
    char* ptr;
    CHAR Buffer[512];

    va_start(ap, Format);
    Length = _vsnprintf(Buffer, sizeof(Buffer), Format, ap);
    va_end(ap);

    /* Check if we went past the buffer */
    if (Length == -1)
    {
        /* Terminate it if we went over-board */
        Buffer[sizeof(Buffer) - 1] = '\n';

        /* Put maximum */
        Length = sizeof(Buffer);
    }

    ptr = Buffer;
    while (Length--)
    {
        if (*ptr == '\n')
            CpPutByte(&KdDebugComPort, '\r');

        CpPutByte(&KdDebugComPort, *ptr++);
    }

    return 0;
}
#endif

/* FUNCTIONS ******************************************************************/

NTSTATUS
NTAPI
KdD0Transition(VOID)
{
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdD3Transition(VOID)
{
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdSave(IN BOOLEAN SleepTransition)
{
    /* Nothing to do on COM ports */
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdRestore(IN BOOLEAN SleepTransition)
{
    /* Nothing to do on COM ports */
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdpPortInitialize(IN ULONG ComPortNumber,
                  IN ULONG ComPortBaudRate)
{
    NTSTATUS Status;

    KDDBGPRINT("KdpPortInitialize, Port = COM%ld\n", ComPortNumber);

    Status = CpInitialize(&KdComPort,
                          UlongToPtr(BaseArray[ComPortNumber]),
                          ComPortBaudRate);
    if (!NT_SUCCESS(Status))
    {
        return STATUS_INVALID_PARAMETER;
    }
    else
    {
        KdComPortInUse = KdComPort.Address;
        return STATUS_SUCCESS;
    }
}

/******************************************************************************
 * \name KdDebuggerInitialize0
 * \brief Phase 0 initialization.
 * \param [opt] LoaderBlock Pointer to the Loader parameter block. Can be NULL.
 * \return Status
 */
NTSTATUS
NTAPI
KdDebuggerInitialize0(IN PLOADER_PARAMETER_BLOCK LoaderBlock OPTIONAL)
{
    ULONG ComPortNumber   = DEFAULT_DEBUG_PORT;
    ULONG ComPortBaudRate = DEFAULT_DEBUG_BAUD_RATE;

    PCHAR CommandLine, PortString, BaudString, IrqString;
    ULONG Value;

    /* Check if we have a LoaderBlock */
    if (LoaderBlock)
    {
        /* Get the Command Line */
        CommandLine = LoaderBlock->LoadOptions;

        /* Upcase it */
        _strupr(CommandLine);

        /* Get the port and baud rate */
        PortString = strstr(CommandLine, "DEBUGPORT");
        BaudString = strstr(CommandLine, "BAUDRATE");
        IrqString  = strstr(CommandLine, "IRQ");

        /* Check if we got the /DEBUGPORT parameter */
        if (PortString)
        {
            /* Move past the actual string, to reach the port*/
            PortString += strlen("DEBUGPORT");

            /* Now get past any spaces and skip the equal sign */
            while (*PortString == ' ') PortString++;
            PortString++;

            /* Do we have a serial port? */
            if (strncmp(PortString, "COM", 3) != 0)
            {
                return STATUS_INVALID_PARAMETER;
            }

            /* Check for a valid Serial Port */
            PortString += 3;
            Value = atol(PortString);
            if (Value >= sizeof(BaseArray) / sizeof(BaseArray[0]))
            {
                return STATUS_INVALID_PARAMETER;
            }

            /* Set the port to use */
            ComPortNumber = Value;
       }

        /* Check if we got a baud rate */
        if (BaudString)
        {
            /* Move past the actual string, to reach the rate */
            BaudString += strlen("BAUDRATE");

            /* Now get past any spaces */
            while (*BaudString == ' ') BaudString++;

            /* And make sure we have a rate */
            if (*BaudString)
            {
                /* Read and set it */
                Value = atol(BaudString + 1);
                if (Value) ComPortBaudRate = Value;
            }
        }

        /* Check Serial Port Settings [IRQ] */
        if (IrqString)
        {
            /* Move past the actual string, to reach the rate */
            IrqString += strlen("IRQ");

            /* Now get past any spaces */
            while (*IrqString == ' ') IrqString++;

            /* And make sure we have an IRQ */
            if (*IrqString)
            {
                /* Read and set it */
                Value = atol(IrqString + 1);
                if (Value) KdComPortIrq = Value;
            }
        }
    }

    /* Get base address */
    ComPortBase = UlongToPtr(BaseArray[ComPortNumber]);

    /* Initialize the port */
    return KdpPortInitialize(ComPortNumber, ComPortBaudRate);
}

/******************************************************************************
 * \name KdDebuggerInitialize1
 * \brief Phase 1 initialization.
 * \param [opt] LoaderBlock Pointer to the Loader parameter block. Can be NULL.
 * \return Status
 */
NTSTATUS
NTAPI
KdDebuggerInitialize1(IN PLOADER_PARAMETER_BLOCK LoaderBlock OPTIONAL)
{
    return STATUS_SUCCESS;
}


VOID
NTAPI
KdpSendByte(IN UCHAR Byte)
{
    // Timing fix!
    READ_PORT_UCHAR(ComPortBase + COM_MSR);

    /* Wait for the port to be ready */
    while ((READ_PORT_UCHAR(ComPortBase + COM_LSR) & LSR_TBE) == 0);
    READ_PORT_UCHAR(ComPortBase + COM_MSR);
    while ((READ_PORT_UCHAR(ComPortBase + COM_LSR) & LSR_TBE) == 0);

    // Timing fix!
    READ_PORT_UCHAR(ComPortBase + COM_MSR);

    /* Send the byte */
    CpPutByte(&KdComPort, Byte);
}

KDP_STATUS
NTAPI
KdpPollByte(OUT PUCHAR OutByte)
{
    UCHAR lsr;

    READ_PORT_UCHAR(ComPortBase + COM_MSR); // Timing
    lsr = READ_PORT_UCHAR(ComPortBase + COM_LSR);

    /* Check if data is available */
    if (lsr & LSR_DR)
    {
        /* Check for error */
        if (lsr & (LSR_FE|LSR_PE|LSR_OE))
        {
            *OutByte = 0;
            return KDP_PACKET_RESEND;
        }

        /* Return the byte */
        return KDP_PACKET_RECEIVED;
    }

    /* No data available. */
    return KDP_PACKET_TIMEOUT;

        case CP_GET_ERROR:
        default:
            return KDP_PACKET_RESEND;
}

KDP_STATUS
NTAPI
KdpReceiveByte(OUT PUCHAR OutByte)
{
    USHORT Status;

    /* Get the byte */
    Status = CpGetByte(&KdComPort, OutByte, TRUE, FALSE);
    switch (Status)
    {
        case CP_GET_SUCCESS:
        return KDP_PACKET_RECEIVED;

        case CP_GET_NODATA:
        return KDP_PACKET_TIMEOUT;

        case CP_GET_ERROR:
        default:
            return KDP_PACKET_RESEND;
    }
}

KDP_STATUS
NTAPI
KdpPollBreakIn(VOID)
{
    KDP_STATUS KdStatus;
    UCHAR Byte;

    KdStatus = KdpPollByte(&Byte);
    if ((KdStatus == KDP_PACKET_RECEIVED) && (Byte == BREAKIN_PACKET_BYTE))
    {
        return KDP_PACKET_RECEIVED;
    }
    return KDP_PACKET_TIMEOUT;
}

/* EOF */
