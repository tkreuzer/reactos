@ stdcall RtlInitializeConditionVariable(ptr) ntdll.RtlInitializeConditionVariable
@ stdcall RtlWakeConditionVariable(ptr) ntdll.RtlWakeConditionVariable
@ stdcall RtlWakeAllConditionVariable(ptr) ntdll.RtlWakeAllConditionVariable
@ stdcall RtlSleepConditionVariableCS(ptr ptr ptr) ntdll.RtlSleepConditionVariableCS
@ stdcall RtlSleepConditionVariableSRW(ptr ptr ptr long) ntdll.RtlSleepConditionVariableSRW
@ stdcall RtlInitializeSRWLock(ptr) ntdll.RtlInitializeSRWLock
@ stdcall RtlAcquireSRWLockShared(ptr) ntdll.RtlAcquireSRWLockShared
@ stdcall RtlReleaseSRWLockShared(ptr) ntdll.RtlReleaseSRWLockShared
@ stdcall RtlAcquireSRWLockExclusive(ptr) ntdll.RtlAcquireSRWLockExclusive
@ stdcall RtlReleaseSRWLockExclusive(ptr) ntdll.RtlReleaseSRWLockExclusive
@ stdcall RtlRunOnceInitialize(ptr) ntdll.RtlRunOnceInitialize
@ stdcall RtlRunOnceBeginInitialize(ptr long ptr) ntdll.RtlRunOnceBeginInitialize
@ stdcall RtlRunOnceComplete(ptr long ptr) ntdll.RtlRunOnceComplete
@ stdcall RtlRunOnceExecuteOnce(ptr ptr ptr ptr) ntdll.RtlRunOnceExecuteOnce
@ stdcall A_SHAFinal(ptr ptr) ntdll.A_SHAFinal
@ stdcall A_SHAInit(ptr) ntdll.A_SHAInit
@ stdcall A_SHAUpdate(ptr ptr long) ntdll.A_SHAUpdate
@ stdcall MD4Final(ptr) ntdll.MD4Final
@ stdcall MD4Init(ptr) ntdll.MD4Init
@ stdcall MD4Update(ptr ptr long) ntdll.MD4Update
@ stdcall MD5Final(ptr) ntdll.MD5Final
@ stdcall MD5Init(ptr) ntdll.MD5Init
@ stdcall MD5Update(ptr ptr long) ntdll.MD5Update
