
.text
.intel_syntax noprefix

.globl _SEHCleanHandlerEnvironment
_SEHCleanHandlerEnvironment:
	ret

.globl _SEHCurrentRegistration
_SEHCurrentRegistration:
	ret

.globl _SEHRegisterFrame
_SEHRegisterFrame:
	ret

.globl _SEHUnregisterFrame
_SEHUnregisterFrame:
	ret

.globl _SEHGlobalUnwind
_SEHGlobalUnwind:

.extern __SEHRtlUnwind

// RtlUnwind clobbers all the "don't clobber" registers, so we save them
	push rbx
	mov rbx, [rsp+8]
	push rsi
	push rdi

	push 0 // ReturnValue
	push 0 // ExceptionRecord
//	push .RestoreRegisters // TargetIp
	push rbx // TargetFrame
//	call [__SEHRtlUnwind]

.RestoreRegisters:
	pop rdi
	pop rsi
	pop rbx

	ret

// EOF
