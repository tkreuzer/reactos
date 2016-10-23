$if (_WDMDDK_)
/** Kernel definitions for IA64 **/

#define PAUSE_PROCESSOR __yield();

FORCEINLINE
VOID
KeFlushWriteBuffer(VOID)
{
  __mf ();
  return;
}

NTSYSAPI
PKTHREAD
NTAPI
KeGetCurrentThread(VOID);

$endif

