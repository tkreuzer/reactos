@ stdcall DbgBreakPoint()
@ stdcall DbgBreakPointWithStatus(long)
@ varargs DbgPrint(str)
@ varargs DbgPrintEx(long long str)
@ stdcall DbgPrompt(ptr ptr long)
@ stdcall RtlAssert(ptr ptr long ptr)
@ stdcall RtlUnwind(ptr ptr ptr ptr)
@ stdcall vDbgPrintExWithPrefix(str long long str ptr)