/*
 * Copyright (c) 2008, KJK::Hyperion
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  - Neither the name of the ReactOS Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

// FIXME: move stubs elsewhere

#include <k32.h>
#include <stdlib.h>

#include <ndk/rtlfuncs.h>

extern "C"
{
void WINAPI EnterCriticalSection(PCRITICAL_SECTION p) { RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)p); }
void WINAPI LeaveCriticalSection(PCRITICAL_SECTION p) { RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)p); }
void WINAPI DeleteCriticalSection(PCRITICAL_SECTION p) { RtlDeleteCriticalSection((PRTL_CRITICAL_SECTION)p); }

void free(void * memory)
{
	RtlFreeHeap(RtlGetProcessHeap(), 0, memory);
}

void * malloc(size_t size)
{
	return RtlAllocateHeap(RtlGetProcessHeap(), 0, size);
}

void * realloc(void * memory, size_t size)
{
	return RtlReAllocateHeap(RtlGetProcessHeap(), 0, memory, size);
}

int __cdecl _purecall()
{
	FatalAppExitW(0, L"pure virtual call");
	FatalExit(0);
	return 0;
}

#if defined(__GNUC__)
__attribute__((alias("_purecall"))) void __cxa_pure_virtual(void);
#endif

void _assert()
{
	FatalAppExitW(0, L"assertion failed");
	FatalExit(0);
}
}

void operator delete(void * memory)
{
	free(memory);
}

// EOF