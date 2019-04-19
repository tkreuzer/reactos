
#include <ntoskrnl.h>

#define COM_LSR 5
#define SR_LSR_DR  0x01
#define SR_LSR_TBE 0x20

static PUCHAR Rs232PortBase = (PUCHAR)(ULONG_PTR)0x3F8;

UCHAR
NTAPI
Rs232PortPollByte()
{
	while ((READ_PORT_UCHAR(Rs232PortBase + COM_LSR) & SR_LSR_DR) == 0)
		;

	return READ_PORT_UCHAR(Rs232PortBase);
}

VOID
NTAPI
Rs232PortPutByte(UCHAR ByteToSend)
{
	while ((READ_PORT_UCHAR(Rs232PortBase + COM_LSR) & SR_LSR_TBE) == 0)
		;

	WRITE_PORT_UCHAR(Rs232PortBase, ByteToSend);
}


ULONG
RawDbgPrint(const char *Format, ...)
{
	int i;
	int Length;
	va_list ap;
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

