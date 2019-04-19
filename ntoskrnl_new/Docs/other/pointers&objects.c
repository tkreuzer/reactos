
/*

    Goals:
    - Make functions generally exception-safe
      - Use static objects / smart-pointers instead of pointers


    Objects:
    - UNICODE_STRING: On destruction, ASSERT that Buffer == NULL
    - UNICODE_STRING_EX: "smart pointer", manages buffer references
      - alt. names: ASTRING, USTRING/WSTRING


*/



class OBJECT_REF
{
    PVOID _ObjectPtr;
    BOOLEAN _NeedsRelease;

    operator=(OBJECT_REF &Source)
    {
        Source->_NeedsRelease = FALSE;
        _NeedsRelease = TRUE;
    }

}

void
foo()
{
    THREAD thread;

    thread.new(...);

}

/// return value optimization!
/// when calling CurrentThread(), don't call the function twice!
/// const vs constexpre vs ..?
FORCEINLINE void throw_x(void)
{
    NT_ASSET(FALSE);
    //KeBugCheck(0);
}

template<typename _T>
FORCEINLINE void throw_x(_T ex)
{
    NT_ASSET(FALSE);
    //KeBugCheck(0);
}

#define throw throw_x(), (void)

void _throw()
{
    ExRaiseException(...);
}

extern "C"
void
__stdcall
_CxxThrowException(
    void* pExceptionObject
    _ThrowInfo* pThrowInfo);


// GCC throw

struct _TI2PEAD
{
    ULONG U1;
    ULONG U2;
    ULONG U3;
    struct _CTA2PEAD *Pointer;
    ULONG U4;
    ULONG U5;
    ULONG U6;
};

struct _CTA2PEAD
{
    ULONG U1;

};


struct __throw_object
{
    template<typename _T>
    __throw_object(const _T &source)
    {
        _CxxThrowException(&source, );
    }

};

namespace GccCompiler {

// http://members.gamedev.net/sicrane/articles/exception.html

typedef void (__cdecl * _PMFN)(void); // despite the static typing, function pointers of
                                      //   type _PMFN are usually used as pointers to other
                                      //   function types
struct _PMD {
  int mdisp;  // member offset
  int pdisp;  // offset of the vtable
  int vdisp;  // offset to displacment inside the vtable
};

struct _s__CatchableType {
  unsigned int      properties;       // bit 1: is a simple type
                                      //   bit 2: can be caught by reference only
                                      //   bit 3: has virtual base
  _TypeDescriptor * pType             // pointer to std::type_info object.
  _PMD              thisDisplacement; // displacement of the object for this type
  int               sizeOrOffset;     // size of the type
  _PMFN             copyFunction;     // pointer to copy constructor or 0
};
typedef const _s__CatchableType _CatchableType;

struct _s__CatchableTypeArray {
  int              nCatchableTypes;         // number of entries in arrayOfCatchableTypes
  _CatchableType * arrayOfCatchableTypes[]; // array of pointers to all base types of the object
                                            //   including types that it can be implicitly cast to
};
typedef const _s__CatchableTypeArray _CatchableTypeArray;

struct _s__ThrowInfo {
  unsigned int          attributes;           // bit 1 for const, bit 2 for volatile
  _PMFN                 pmfnUnwind;           // function to destroy the exception object
  int        (__cdecl * pForwardCompat)(...);
  _CatchableTypeArray * pCatchableTypeArray;  // pointer to array of pointers to type information
};
typedef const _s__ThrowInfo _ThrowInfo;

template<typename _T>
class CThrowData
{
    static const _CatchableTypeArray s_CatchableTypeArray =
    {
    };

    static const _s__ThrowInfo s_ThrowInfo =
    {
        type_info<_T>::IsConst * 1 + type_info<_T>::IsVolatile * 2,
        0, // FIXME
        0, // FIXME
        &s_CatchableTypeArray
    };
}

class CThrowObject
{


public:

    template<typename _T>
    CThrowObject(const _T &Object)
    {
        _CxxThrowException(&Object, &CThrowData<_T>::s_ThrowInfo );
    }


};

} // namespace GccCompiler

#define throw ::GccCompiler::CThrowObject throwObject =
