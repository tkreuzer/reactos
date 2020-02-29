
@ stdcall InitOnceExecuteOnce(ptr ptr ptr ptr) kernel32.InitOnceExecuteOnce
@ stdcall GetFileInformationByHandleEx(long long ptr long) kernel32.GetFileInformationByHandleEx
@ stdcall -ret64 GetTickCount64() kernel32.GetTickCount64

@ stdcall InitializeSRWLock(ptr) kernel32.InitializeSRWLock
@ stdcall AcquireSRWLockExclusive(ptr) kernel32.AcquireSRWLockExclusive
@ stdcall AcquireSRWLockShared(ptr) kernel32.AcquireSRWLockShared
@ stdcall ReleaseSRWLockExclusive(ptr) kernel32.ReleaseSRWLockExclusive
@ stdcall ReleaseSRWLockShared(ptr) kernel32.ReleaseSRWLockShared

@ stdcall InitializeConditionVariable(ptr) kernel32.InitializeConditionVariable
@ stdcall SleepConditionVariableCS(ptr ptr long) kernel32.SleepConditionVariableCS
@ stdcall SleepConditionVariableSRW(ptr ptr long long) kernel32.SleepConditionVariableSRW
@ stdcall WakeAllConditionVariable(ptr) kernel32.WakeAllConditionVariable
@ stdcall WakeConditionVariable(ptr) kernel32.WakeConditionVariable

@ stdcall InitializeCriticalSectionEx(ptr long long) kernel32.InitializeCriticalSectionEx

@ stdcall ApplicationRecoveryFinished(long) kernel32.ApplicationRecoveryFinished
@ stdcall ApplicationRecoveryInProgress(ptr) kernel32.ApplicationRecoveryInProgress
@ stdcall CreateSymbolicLinkA(str str long) kernel32.CreateSymbolicLinkA
@ stdcall CreateSymbolicLinkW(wstr wstr long) kernel32.CreateSymbolicLinkW
@ stdcall GetApplicationRecoveryCallback(ptr ptr ptr ptr ptr) kernel32.GetApplicationRecoveryCallback
@ stdcall GetApplicationRestart(ptr wstr ptr ptr) kernel32.GetApplicationRestart
@ stdcall GetFileBandwidthReservation(ptr ptr ptr ptr ptr ptr) kernel32.GetFileBandwidthReservation
@ stdcall GetFileMUIInfo(long wstr ptr ptr) kernel32.GetFileMUIInfo
@ stdcall GetFileMUIPath(long wstr wstr ptr wstr ptr ptr) kernel32.GetFileMUIPath
@ stdcall GetFinalPathNameByHandleA(ptr str long long) kernel32.GetFinalPathNameByHandleA
@ stdcall GetFinalPathNameByHandleW(ptr wstr long long) kernel32.GetFinalPathNameByHandleW
@ stdcall GetSystemPreferredUILanguages(long ptr wstr ptr) kernel32.GetSystemPreferredUILanguages
@ stdcall GetThreadPreferredUILanguages(long ptr wstr ptr) kernel32.GetThreadPreferredUILanguages
@ stdcall GetThreadUILanguage() kernel32.GetThreadUILanguage
@ stdcall GetUILanguageInfo(long wstr wstr ptr ptr) kernel32.GetUILanguageInfo
@ stdcall GetUserPreferredUILanguages(long ptr wstr ptr) kernel32.GetUserPreferredUILanguages
@ stdcall OpenFileById(ptr ptr long long ptr long) kernel32.OpenFileById
@ stdcall QueryFullProcessImageNameA(ptr long str ptr) kernel32.QueryFullProcessImageNameA
@ stdcall QueryFullProcessImageNameW(ptr long wstr ptr) kernel32.QueryFullProcessImageNameW
@ stdcall RegisterApplicationRecoveryCallback(ptr ptr long long) kernel32.RegisterApplicationRecoveryCallback
@ stdcall RegisterApplicationRestart(wstr long) kernel32.RegisterApplicationRestart
@ stdcall SetFileBandwidthReservation(ptr long long long ptr ptr) kernel32.SetFileBandwidthReservation
@ stdcall SetThreadPreferredUILanguages(long wstr ptr) kernel32.SetThreadPrefe
