

#pragma once

#include <Context.hpp>


/*

    Exception handling
    ------------------

    throw is allowed with the following types:
    - NTSTATUS: Initializes a RuntimeError exception
    -


    GCC: throw keyword will be define to use a custom construct, that will
    result in setting up the required data and calling _CxxThrowException.
    The only catchable exception is the EXCEPTION class. It will accept all
    thrown objects, the _ThrowInfo passed to _CxxThrowException will contain
    the EXCEPTION class and a limited set of alternative types.

    Stack: Last kernel stack page is marked as inaccessible. When it's accessed,
    a stack exception will occur, which will be executed on a special stack.
    The exception handler will make the last stack page valid and throw the
    appropriate C++ exception. The exception handling code will call the
    catch handler and when it returns, unwind the stack back to the handler
    and then call the appropriate cleanup function.

    it will be made valid, and a kernel stack exception is thrown.


*/

enum EXCEPTION_CLASS
{
    HardwareException,
    RuntimeError,
    UnknownRuntimeException,

};

class EXCEPTION_BASE
{
protected:

    template<typename _T>
    struct BaseClass
    {
        typedef BaseClass<_T>::type type;
    };

    template<>
    struct BaseClass<EXCEPTION>
    {
        typedef EXCEPTION type;
    };

    typedef EXCEPTION_BASE super;

};

class EXCEPTION : public EXCEPTION_BASE
{
    EXCEPTION_CLASS _ExceptionClass;
    union
    {
        NTSTATUS _StatusCode;
        EXCEPTION_CODE _ExceptionCode;
    };
    CONTEXT _ExceptionContext;
    PVOID _StackBackTrace[MAX_BACKTRACE_DEPTH];
    PCSTR _ExceptionText;

protected:

    typedef super::type super;

public:

    EXCEPTION (
        _In_ NTSTATUS StatusCode
        );

    EXCEPTION (
        _In_ PTRAP_FRAME TrapFrame
        );

    template<class _CLASS>
    EXCEPTION (
        _In_ _CLASS *Object
        );


};
