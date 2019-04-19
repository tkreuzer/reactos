
#include <ntbase.h>
#include <intrin.h>
#include <stdarg.h>
#include <stdio.h>

#define COM_LSR 5
#define SR_LSR_DR  0x01
#define SR_LSR_TBE 0x20

static USHORT Rs232PortBase = 0x3F8;

UCHAR
NTAPI
Rs232PortPollByte()
{
	while ((__inbyte(Rs232PortBase + COM_LSR) & SR_LSR_DR) == 0)
		;

	return __inbyte(Rs232PortBase);
}

VOID
NTAPI
Rs232PortPutByte(UCHAR ByteToSend)
{
	while ((__inbyte(Rs232PortBase + COM_LSR) & SR_LSR_TBE) == 0)
		;

	__outbyte(Rs232PortBase, ByteToSend);
}

extern "C"
UINT
RawDbgPrint(const char *Format, ...)
{
	UINT i;
	UINT Length;
	va_list ap;
	CHAR Buffer[512];

	va_start(ap, Format);
	Length = _vsnprintf(Buffer, sizeof(Buffer), Format, ap);
	va_end(ap);

	/* Check if we went past the buffer */
	if (Length == -1)
	{
		/* Terminate it with a newline */
		Buffer[sizeof(Buffer) - 1] = '\n';

		/* Set maximum */
		Length = sizeof(Buffer);
	}

    /* Loop all characters */
	for (i = 0; i < Length; i++)
	{
	    /* Check for newline character */
        if (Buffer[i] == '\n')
        {
            /* Make it CR/LF */
            Rs232PortPutByte('\r');
        }
		Rs232PortPutByte(Buffer[i]);
	}

	return Length;
}

