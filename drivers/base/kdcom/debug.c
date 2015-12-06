/*
 * COPYRIGHT:       GPL, see COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            drivers/base/kddll/kddll.c
 * PURPOSE:         Base functions for the kernel debugger.
 * PROGRAMMER:      Timo Kreuzer (timo.kreuzer@ewactos.org)
 */
#if 0
#include "kddll.h"
#include "kdcom.h"
#include <stdio.h>

#define KDDBG_PORT 0x2F8
#define KDDBG_BAUD_RATE 115200

VOID
KdpDbgPutChar(char chr);

VOID
NTAPI
KdpDbgInitialize(void)
{
    ULONG Mode;

    /* Enable loop mode (set Bit 4 of the MCR) */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_MCR, MCR_LOOP);

    /* Enable FIFO */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_FCR,
                     FCR_ENABLE_FIFO | FCR_CLEAR_RCVR | FCR_CLEAR_XMIT);

    /* Disable interrupts */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_LCR, 0);
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_IEN, 0);

    /* Enable on DTR and RTS  */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_MCR, MCR_DTR | MCR_RTS);

    /* Set DLAB */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_LCR, LCR_DLAB);

    /* Set baud rate */
    Mode = 115200 / KDDBG_BAUD_RATE;
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_DLL, (UCHAR)(Mode & 0xff));
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_DLM, (UCHAR)((Mode >> 8) & 0xff));

    /* Reset DLAB and set 8 data bits, 1 stop bit, no parity, no break */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_LCR, LCR_CS8 | LCR_ST1 | LCR_PNO);

WRITE_PORT_UCHAR(KDDBG_PORT + COM_DAT, 'x');

KdpDbgPutChar('<');

    KdpDbgPrint("Serial debugging initialized\n");
}

VOID
KdpDbgPutChar(char chr)
{
    /* Wait for the port to be ready */
    while ((READ_PORT_UCHAR(KDDBG_PORT + COM_LSR) & LSR_TBE) == 0);

    /* Send the byte */
    WRITE_PORT_UCHAR(KDDBG_PORT + COM_DAT, chr);
}

ULONG
KdpDbgPrint(const char *fmt, ...)
{
    va_list args;
    unsigned int i, len;
    char Buffer[1024];

    va_start(args, fmt);
    len = _vsnprintf(Buffer, 1023, fmt, args);
    va_end(args);

    for (i = 0; i < len; i++) KdpDbgPutChar(Buffer[i]);
    return i;
}
#endif
