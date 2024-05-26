//
// internal_shared.h
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Header for definitions shared between vcruntime and UCRT.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <suppress.h>
#include <intrin.h>
#include <corecrt_startup.h>
#include <windows.h> // for HMODULE

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define _CRTALLOC(x) __declspec(allocate(x))
#pragma section(".CRT$XIC", long, read)
#pragma section(".CRT$XPX", long, read)
#pragma section(".CRT$XPXA", long, read)

#pragma section(".CRT$XIA", long, read)
#pragma section(".CRT$XIZ", long, read)
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)
#pragma section(".CRT$XPA", long, read)
#pragma section(".CRT$XPZ", long, read)
#pragma section(".CRT$XTA", long, read)
#pragma section(".CRT$XTZ", long, read)

extern _PIFV __xi_a[];
extern _PIFV __xi_z[];
extern _PVFV __xc_a[];
extern _PVFV __xc_z[];
extern _PVFV __xp_a[];
extern _PVFV __xp_z[];
extern _PVFV __xt_a[];
extern _PVFV __xt_z[];

extern char __ImageBase;

#define CRT_WARNING_DISABLE_PUSH(wn, message) \
    __pragma(warning(push)) \
    __pragma(warning(disable: wn))

#define CRT_WARNING_POP \
    __pragma(warning(pop))

#define _BEGIN_SECURE_CRT_DEPRECATION_DISABLE \
    __pragma(warning(push)) \
    __pragma(warning(disable: 4996))

#define _END_SECURE_CRT_DEPRECATION_DISABLE \
    __pragma(warning(pop))

#define _CRT_DEBUGGER_IGNORE -1
#define _CRT_DEBUGGER_GSFAILURE 1
#define _CRT_DEBUGGER_INVALIDPARAMETER 2
#define _CRT_DEBUGGER_ABORT 3

#define _CRT_DEBUGGER_HOOK(x)

#define _CRT_SECURITYCRITICAL_ATTRIBUTE
#define _CRT_SECURITYSAFECRITICAL_ATTRIBUTE

#define _VALIDATE_RETURN_NOERRNO(expression, retvalue) \
    if (!(expression)) { \
        return retvalue; \
    }

#define _VALIDATE_RETURN_VOID(expression, errorcode) \
    if (!(expression)) { \
        errno = errorcode; \
        return; \
    }

#define _VALIDATE_RETURN(expression, errorcode, retvalue) \
    if (!(expression)) { \
        errno = errorcode; \
        return retvalue; \
    }

#define _VALIDATE_RETURN_ERRCODE(expression, errorcode) \
    _VALIDATE_RETURN(expression, errorcode, errorcode)

#define _VALIDATE_CLEAR_OSSERR_RETURN(expression, errorcode, retvalue) \
    if (!(expression)) { \
        _doserrno = 0; \
        errno = errorcode; \
        return retvalue; \
    }

#define _VALIDATE_CLEAR_OSSERR_RETURN_ERRCODE(expression, errorcode) \
    _VALIDATE_CLEAR_OSSERR_RETURN(expression, errorcode, errorcode)

#define _VALIDATE_RETURN_NOEXC(expression, errorcode, retvalue) \
    if (!(expression)) { \
        errno = errorcode; \
        return retvalue; \
    }

#define _VALIDATE_RETURN_ERRCODE_NOEXC(expression, errorcode) \
    if (!(expression)) { \
        errno = errorcode; \
        return errorcode; \
    }

#define _malloc_crt malloc
#define _free_crt free
#define _calloc_crt calloc
#define _recalloc_crt _recalloc
#define _malloca_crt _malloca
#define _freea_crt _freea

#ifdef __cplusplus
} // extern "C"

template<typename T>
__forceinline
T __crt_fast_encode_pointer(T ptr)
{
    // FIXME: use cookie
    return ptr;
}

template<typename T>
__forceinline
T __crt_fast_decode_pointer(T ptr)
{
    // FIXME: use cookie
    return ptr;
}

template<typename T>
T __crt_interlocked_read(const T volatile* ptr)
{
    return *ptr;
}

template<typename T>
T __crt_interlocked_read_pointer(const T volatile* ptr)
{
    return *ptr;
}

template<typename T>
T __crt_interlocked_exchange_pointer(T *ptr, void* value)
{
    return (T)_InterlockedExchangePointer((void* volatile*)ptr, value);
}

template<typename T>
struct __crt_seh_guarded_call
{
    template<typename Init, typename Action, typename Cleanup>
    T operator()(Init init, Action action, Cleanup cleanup)
    {
        init();
        __try
        {
            return action();
        }
        __finally
        {
            cleanup();
        }
    }
};

template<typename FuncPtr>
FuncPtr __crt_get_proc_address(HMODULE module, const char* name)
{
    return (FuncPtr)GetProcAddress(module, name);
}

template<typename Action, typename Cleanup>
void __crt_call_and_cleanup(Action action, Cleanup cleanup)
{
    // FIXME: This is probably bogus
    action();
    cleanup();
}

struct __crt_malloc_free_policy
{
    void operator()(void* const ptr) throw()
    {
        _free_crt(ptr);
    }
};

template <typename T, typename FreePolicy = __crt_malloc_free_policy>
class __crt_unique_heap_ptr
{
    T* _ptr;
public:
    __crt_unique_heap_ptr() : _ptr(nullptr) {}
    __crt_unique_heap_ptr(T* ptr) : _ptr(ptr) {}
     ~__crt_unique_heap_ptr() { _free_crt((void*)_ptr); }
     void attach(T* ptr) { _free_crt(_ptr); _ptr = ptr; }
     T* detach() { T* ptr = _ptr; _ptr = nullptr; return ptr; }
     operator bool() const { return _ptr != nullptr; }
     T* get() const { return _ptr; }
     T** get_address_of() { return &_ptr; }
#if 0
     T& operator*() const { return *_ptr; }
     T* operator->() const { return _ptr; }
     operator T*() const { return _ptr; }
#endif
};

struct __crt_public_free_policy
{
    void operator()(void* const ptr) throw()
    {
        _freea_crt(ptr);
    }
};

template <typename T>
using __crt_scoped_stack_ptr = __crt_unique_heap_ptr<T, __crt_public_free_policy>;

#define _malloc_crt_t(t, n) (__crt_unique_heap_ptr<t>(static_cast<t*>(_malloc_crt((n) * sizeof(t)))))
#define _calloc_crt_t(t, n) (__crt_unique_heap_ptr<t>(static_cast<t*>(_calloc_crt((n),  sizeof(t)))))
#define _recalloc_crt_t(t, p, n) (__crt_unique_heap_ptr<t>(static_cast<t*>(_recalloc_crt(p, (n), sizeof(t)))))
#define _malloca_crt_t(t, n) (__crt_scoped_stack_ptr<t>(static_cast<t*>(_malloca_crt((n) * sizeof(t)))))

#if 0
template <typename T>
class __crt_scoped_stack_ptr
{
    T* _ptr;
public:
    __crt_scoped_stack_ptr() : _ptr(nullptr) {}
    __crt_scoped_stack_ptr(T* ptr) : _ptr(ptr) {}
     ~__crt_scoped_stack_ptr() { _freea_crt((void*)_ptr); }
     void attach(T* ptr) { _freea_crt(_ptr); _ptr = ptr; }
     T* detach() { T* ptr = _ptr; _ptr = nullptr; return ptr; }
     operator bool() const { return _ptr != nullptr; }
     T* get() const { return _ptr; }
     T** get_address_of() { return &_ptr; }
};
#endif

#endif // __cplusplus

// HACK!
#define __acrt_select_exit_lock() __acrt_os_exit_lock
