
#define _SA_SPECSTRIZE(x)           #x

#if _USE_DECLSPECS_FOR_SAL

#define _SA_annotes0(n)             __declspec(#n)
#define _SA_annotes1(n,pp1)         __declspec(#n "(" _SA_SPECSTRIZE(pp1) ")" )
#define _SA_annotes2(n,pp1,pp2)     __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) ")")
#define _SA_annotes3(n,pp1,pp2,pp3) __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) "," _SA_SPECSTRIZE(pp3) ")")

#define _SA_Deref_pre1_(p1)         _Pre_ _Notref_ _SA_Deref_ p1
#define _SA_Deref_post1_(p1)        _Post_ _Notref_ _SA_Deref_ p1
#define _SA_Deref_in_bound_         _Pre_ _Notref_ _SA_Deref_ _SA_Bound_
#define _SA_Pre1_(p1)               _SA_Pre_ p1
#define _SA_Pre2_(p1,p2)            _SA_Pre_ p1 _SA_Pre_ p2
#define _SA_Pre3_(p1,p2,p3)         _SA_Pre_ p1 _SA_Pre_ p2 _SA_Pre_ p3
#define _SA_Post1_(p1)              _SA_Post_ p1
#define _SA_Post2_(p1,p2)           _SA_Post_ p1 _SA_Post_ p2
#define _SA_Post3_(p1,p2,p3)        _SA_Post_ p1 _SA_Post_ p2 _SA_Post_ p3

#define __null_impl_notref          _Notref_ _Null_
#define __notnull_impl_notref       _Notref_ _Notnull_
#define __maybenull_impl_notref     _Notref_ _Maybenull_
#define __valid_impl                _SA_annotes0(SAL_valid) // _SA_annotes1(SAL_valid, __yes)
#define __maybevalid_impl           _SA_annotes0(SAL_maybevalid) // _SA_annotes1(SAL_valid, __maybe)
#define __notvalid_impl             _SA_annotes0(SAL_notvalid) // _SA_annotes1(SAL_valid, __no)
#define __readaccess_impl_notref    _Notref_ _SA_annotes0(SAL_readonly) //_SA_annotes1(SAL_access, 0x1)
#define __writeaccess_impl_notref   _Notref_ _SA_annotes0(SAL_notreadonly) // _SA_annotes1(SAL_access, 0x2)
#define __bytecap_impl(size)        _SA_annotes1(SAL_writableTo,byteCount(size))
#define __cap_impl(size)            _SA_annotes1(SAL_writableTo,elementCount(size))
#define __cap_c_one_notref_impl     _Notref_ _SA_annotes1(SAL_writableTo,elementCount(1))
#define __bytecount_impl(size)      _SA_annotes1(SAL_readableTo,byteCount(size))
#define __count_impl(size)          _SA_annotes1(SAL_readableTo,elementCount(size))

#elif _USE_ATTRIBUTES_FOR_SAL

#if (_MSC_VER < 1400)
#error attribute sal only works with _MSC_VER >= 1400
#endif

#if !defined(_W64)
# if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#  define _W64 __w64
# else
#  define _W64
# endif
#endif

#ifndef _SIZE_T_DEFINED
# ifdef  _WIN64
typedef unsigned __int64 size_t;
# else
typedef _W64 unsigned int size_t;
# endif
# define _SIZE_T_DEFINED
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
# define _WCHAR_T_DEFINED
#endif

#ifdef __cplusplus
# define SA(id) id
# define REPEATABLE [repeatable]
# define CONSTRUCTOR(name) name();
namespace vc_attributes {
#else
# define SA(id) SA_##id
# define REPEATABLE
# define CONSTRUCTOR(name)
#endif
#define ATTR_SA_ALL [source_annotation_attribute(SA(All))]

typedef enum SA(YesNoMaybe)
{
	SA(No) = 0x0fff0001,
	SA(Maybe) = 0x0fff0010,
	SA(Yes) = 0x0fff0100
} SA(YesNoMaybe);

typedef enum SA(AccessType)
{
	SA(NoAccess) = 0,
	SA(Read) = 1,
	SA(Write) = 2,
	SA(ReadWrite) = 3
} SA(AccessType);

#define DECLARE_ATTR(Name, ...) \
    ATTR_SA_ALL \
    typedef struct Name \
    { \
        CONSTRUCTOR(Name) \
        __VA_ARGS__ \
    } Name,

REPEATABLE DECLARE_ATTR(PreAttribute, unsigned int Deref;SA(YesNoMaybe) Valid;SA(YesNoMaybe) Null;SA(YesNoMaybe) Tainted;SA(AccessType) Access;unsigned int Notref;
    size_t ValidElementsConst;size_t ValidBytesConst;const wchar_t* ValidElements;const wchar_t* ValidBytes;const wchar_t* ValidElementsLength;const wchar_t* ValidBytesLength;
	size_t WritableElementsConst;size_t WritableBytesConst;const wchar_t* WritableElements;const wchar_t* WritableBytes;const wchar_t* WritableElementsLength;
	const wchar_t* WritableBytesLength;size_t ElementSizeConst;const wchar_t* ElementSize;SA(YesNoMaybe) NullTerminated;const wchar_t* Condition;) SA_Pre;
REPEATABLE DECLARE_ATTR(PostAttribute, unsigned int Deref;SA(YesNoMaybe) Valid;SA(YesNoMaybe) Null;SA(YesNoMaybe) Tainted;SA(AccessType) Access;
	unsigned int Notref;size_t ValidElementsConst;size_t ValidBytesConst;const wchar_t* ValidElements;const wchar_t* ValidBytes;
	const wchar_t* ValidElementsLength;const wchar_t* ValidBytesLength;size_t WritableElementsConst;size_t WritableBytesConst;
	const wchar_t* WritableElements;const wchar_t* WritableBytes;const wchar_t* WritableElementsLength;const wchar_t* WritableBytesLength;
	size_t ElementSizeConst;const wchar_t* ElementSize;SA(YesNoMaybe) NullTerminated;SA(YesNoMaybe) MustCheck;const wchar_t* Condition;) SA_Post;
DECLARE_ATTR(FormatStringAttribute, const wchar_t* Style; const wchar_t* UnformattedAlternative;) SA_FormatString;
REPEATABLE DECLARE_ATTR(PreBoundAttribute, unsigned int Deref;) SA_PreBound;
REPEATABLE DECLARE_ATTR(PostBoundAttribute, unsigned int Deref;) SA_PostBound;
REPEATABLE DECLARE_ATTR(PreRangeAttribute, unsigned int Deref;const char* MinVal;const char* MaxVal;) SA_PreRange;
REPEATABLE DECLARE_ATTR(PostRangeAttribute, unsigned int Deref;const char* MinVal;const char* MaxVal;) SA_PostRange;
REPEATABLE DECLARE_ATTR(DerefAttribute, int unused;) SAL_deref;
REPEATABLE DECLARE_ATTR(NotrefAttribute, int unused;) SAL_notref;
REPEATABLE DECLARE_ATTR(AnnotesAttribute, wchar_t *Name;wchar_t *p1;wchar_t *p2;wchar_t *p3;wchar_t *p4;wchar_t *p5;wchar_t *p6;wchar_t *p7;wchar_t *p8;wchar_t *p9;) SAL_annotes;
REPEATABLE DECLARE_ATTR(AtAttribute, wchar_t *p1;) SAL_at;
REPEATABLE DECLARE_ATTR(AtBufferAttribute, wchar_t *p1;wchar_t *p2;wchar_t *p3;) SAL_at_buffer;
REPEATABLE DECLARE_ATTR(WhenAttribute, wchar_t *p1;) SAL_when;
REPEATABLE DECLARE_ATTR(TypefixAttribute, wchar_t *p1;) SAL_typefix;
REPEATABLE DECLARE_ATTR(ContextAttribute, wchar_t *p1;) SAL_context;
REPEATABLE DECLARE_ATTR(ExceptAttribute, int unused;) SAL_except;
REPEATABLE DECLARE_ATTR(PreOpAttribute, int unused;) SAL_pre;
REPEATABLE DECLARE_ATTR(PostOpAttribute, int unused;) SAL_post;
REPEATABLE DECLARE_ATTR(BeginAttribute, int unused;) SAL_begin;
REPEATABLE DECLARE_ATTR(EndAttribute, int unused;) SAL_end;

#ifdef __cplusplus
};
#endif

#undef REPEATABLE
#undef SA
#undef DECLARE_ATTR

#if (_MSC_VER >= 1610)
#define _NL_(size) "\n"#size
#else
#define _NL_(size) #size
#endif

#define _SA_annotes0(n)             [SAL_annotes(Name=#n)]
#define _SA_annotes1(n,pp1)         [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1))]
#define _SA_annotes2(n,pp1,pp2)     [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1), p2=_SA_SPECSTRIZE(pp2))]
#define _SA_annotes3(n,pp1,pp2,pp3) [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1), p2=_SA_SPECSTRIZE(pp2), p3=_SA_SPECSTRIZE(pp3))]

#define _SA_Deref_pre1_(p1)         [SA_Pre(Deref=1,p1)]
#define _SA_Deref_post1_(p1)        [SA_Post(Deref=1,p1)]
#define _SA_Deref_in_bound_         [SA_PreBound(Deref=1)]
#define _SA_Pre1_(p1)               [SA_Pre(p1)]
#define _SA_Pre2_(p1,p2)            [SA_Pre(p1,p2)]
#define _SA_Pre3_(p1,p2,p3)         [SA_Pre(p1,p2,p3)]
#define _SA_Post1_(p1)              [SA_Post(p1)]
#define _SA_Post2_(p1,p2)           [SA_Post(p1,p2)]
#define _SA_Post3_(p1,p2,p3)        [SA_Post(p1,p2,p3)]

#define __null_impl_notref          Null=SA_Yes,Notref=1
#define __notnull_impl_notref       Null=SA_No,Notref=1
#define __maybenull_impl_notref     Null=SA_Maybe,Notref=1
#define __valid_impl                Valid=SA_Yes
#define __notvalid_impl             Valid=SA_No
#define __maybevalid_impl           Valid=SA_Maybe
#define __readaccess_impl_notref    Access=SA_Read,Notref=1
#define __writeaccess_impl_notref   Access=SA_Write,Notref=1
#define __bytecap_impl(size)        WritableBytes=_NL_(size)
#define __cap_impl(size)            WritableElements=_NL_(size)
#define __cap_c_one_notref_impl     WritableElementsConst=1,Notref=1
#define __bytecount_impl(size)      ValidBytes=_NL_(size)
#define __count_impl(size)          ValidElements=_NL_(size)

#endif


/* Common internal */
#define _SA_Bound_                  _SA_annotes0(SAL_bound)
#define _SA_Deref_                  _SA_annotes0(SAL_deref)
#define _SA_Pre_                    _SA_annotes0(SAL_pre)
#define _SA_Post_                   _SA_annotes0(SAL_post)
#define _SA_Satisfies_(cond)        _SA_annotes1(SAL_satisfies, cond)
#define _SA_Must_inspect_           _Post_ _SA_annotes0(SAL_mustInspect)

/******************************************************************************/

/* Implementation layer */
#define _Post_                      _SA_annotes0(SAL_post)
#define _Pre_                       _SA_annotes0(SAL_pre)
#ifdef __cplusplus
#define _Notref_                    _SA_annotes0(SAL_notref)
#else
#define _Notref_
#endif
#define _Null_                      _SA_annotes1(SAL_null, __yes)
#define _Notnull_                   _SA_annotes1(SAL_null, __no)
#define _Maybenull_                 _SA_annotes1(SAL_null, __maybe)
#define _Valid_                     _SA_annotes1(SAL_valid, __yes)
#define _Notvalid_                  _SA_annotes1(SAL_valid, __no)
#define _Maybevalid_                _SA_annotes1(SAL_valid, __maybe)
#define _Literal_                   _SA_annotes1(SAL_constant, __yes)
#define _Notliteral_                _SA_annotes1(SAL_constant, __no)
#define	_Null_terminated_           _SA_annotes1(SAL_nullTerminated, __yes)
#define _Field_range_(min,max)      _SA_annotes2(SAL_range, min, max)
#define	_Readable_bytes_(size)      _SA_annotes1(SAL_readableTo, byteCount(size))
#define	_Readable_elements_(size)   _SA_annotes1(SAL_readableTo, elementCount(size))
#define	_Writable_bytes_(size)      _SA_annotes1(SAL_writableTo, byteCount(size))
#define	_Writable_elements_(size)   _SA_annotes1(SAL_writableTo, elementCount(size))
#define	_Success_(expr)             _SA_annotes1(SAL_success, expr)
#define	_When_(expr, annos)         _SA_annotes0(SAL_when(expr)) _Group_(annos)
#define _Group_(annos)              _SA_annotes0(SAL_begin) annos _SA_annotes0(SAL_end)
#define	_On_failure_(annos)         _SA_annotes1(SAL_context, SAL_failed) _Group_(_SA_Post_ _Group_(annos))
#define	_At_(target, annos)         _SA_annotes0(SAL_at(target)) _Group_(annos)
#define	_At_buffer_(t, i, b, a)     _SA_annotes3(SAL_at_buffer, t, i, b) _Group_(a)
#define _Must_inspect_result_       _SA_Must_inspect_ _Check_return_

#define _Pre_null_                  _SA_Pre1_(__null_impl_notref)
#define _Pre_notnull_               _SA_Pre1_(__notnull_impl_notref)
#define _Pre_maybenull_             _SA_Pre1_(__maybenull_impl_notref)
#define	_Pre_valid_                 _SA_Pre1_(__valid_impl)
#define _Pre_invalid_               _SA_Deref_pre1_(__notvalid_impl) // note: this is appied to the memory referenced by the parameter! Same as _Deref_pre_invalid_
#define _Pre_opt_valid_             _SA_Pre1_(__maybenull_impl_notref) _Pre_valid_
#define _Pre_readonly_              _SA_Pre1_(__readaccess_impl_notref)
#define _Pre_writeonly_             _SA_Pre1_(__writeaccess_impl_notref)

#define _Pre_cap_c_one_             _Pre_notnull_ _SA_Pre1_(__cap_c_one_notref_impl)
#define	_Pre_satisfies_(cond)       _SA_Pre_ _SA_Satisfies_(cond)

#define _Post_null_                 _SA_Post1_(__null_impl_notref)
#define _Post_notnull_              _SA_Post1_(__notnull_impl_notref)
#define _Post_maybenull_            _SA_Post1_(__maybenull_impl_notref)
#define	_Post_valid_                _SA_Post1_(__valid_impl)
#define _Post_invalid_              _SA_Post1_(__notvalid_impl)

#define _Post_cap_(size)            _SA_Post1_(__cap_impl(size))
#define _Post_bytecap_(size)        _SA_Post1_(__bytecap_impl(size))

#define	_Post_satisfies_(cond)      _SA_Post_ _SA_Satisfies_(cond)

#define _Deref_pre_readonly_        _SA_Deref_pre1_(__readaccess_impl_notref)
#define _Deref_pre_valid_           _SA_Deref_pre1_(__notnull_impl_notref) _Pre_valid_
#define _Deref_pre_invalid_         _SA_Deref_pre1_(__notvalid_impl)
#define _Deref_post_maybenull_      _SA_Deref_post1_(__maybenull_impl_notref)
#define _Deref_post_opt_valid_      _Deref_post_maybenull_ _Post_valid_
#define _Deref_post_null_           _SA_Deref_post1_(__null_impl_notref)
#define _Deref_post_notnull_        _SA_Deref_post1_(__notnull_impl_notref)

#define _Deref_post_valid_          _Pre_notnull_ _When_(1 == 1, _SA_Deref_pre1_(__maybevalid_impl)) _SA_Deref_post1_(__valid_impl)
//#define _Deref_post_valid_          _Deref_post_notnull_ _Post_valid_ // <- ms implementaton


#define _In_                        _Pre_notnull_ _Pre_valid_ _Deref_pre_readonly_

#define _Out_                       _Pre_cap_c_one_ _Post_valid_ _Deref_post_maybenull_

#define _Deref_out_                 _Out_ _Deref_post_valid_
#define _Deref_out_opt_             _Out_ _Deref_post_opt_valid_
#define _Deref_opt_out_             _Out_opt_ _Deref_post_valid_
#define _Deref_opt_out_opt_         _Out_opt_ _Deref_post_opt_valid_



#if _USE_DECLSPECS_FOR_SAL

#define _Check_return_              _Post_ __declspec("SAL_checkReturn")

#elif _USE_ATTRIBUTES_FOR_SAL

#define _Check_return_              [returnvalue:SA_Post(MustCheck=SA_Yes)]

#endif
