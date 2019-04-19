
- ntoskrnl
- hal
- NUKE
  - Scheduler
    - amd64
    - i386
    - arm
  - HAL -> hal.h (public) / hal_private.h
    - amd64
    - arm
    - i386
    - pc

  - nukrnl.sys (portable!)
    - NtKe
    - NtMm
    - NtOb
    - Debugger


HAL:
  - Exception/Trap/Interrupt handling
  - Timer


ScGetNextReadyThread()
ScSwapThread()


XlInitialize()
