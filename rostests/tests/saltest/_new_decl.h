
#define _SA_SPECSTRIZE(x) #x
#define _SA_annotes0(n)                __declspec(#n)
#define _SA_annotes1(n,pp1)            __declspec(#n "(" _SA_SPECSTRIZE(pp1) ")" )
#define _SA_annotes2(n,pp1,pp2)        __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) ")")
#define _SA_annotes3(n,pp1,pp2,pp3)    __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) "," _SA_SPECSTRIZE(pp3) ")")


#define _Pre_invalid_                   _Deref_pre1_impl_(__notvalid_impl)
#define _Deref_pre_invalid_             _Deref_pre1_impl_(__notvalid_impl)
    -> [SA_Pre(Deref=1,__notvalid_impl)] -> [SA_Pre(Deref=1,Valid=SA_No)]
    -> _Deref_pre_impl_ __notvalid_impl -> _Deref_pre_impl_ _SA_annotes1(SAL_valid, __no)
        -> _Pre_impl_ _Notref_impl_ _Deref_impl_ __declspec("SAL_valid(__no)")
        -> _Pre_ _Notref_ _Deref_ _Invalid_



/* Common layer */
#define _Null_                     _SA_annotes1(SAL_null, __yes)
#define _Notnull_                  _SA_annotes1(SAL_null, __no)
#define _Maybenull_                _SA_annotes1(SAL_null, __maybe)
#define _Valid_                    _SA_annotes1(SAL_valid, __yes)
#define _Notvalid_                 _SA_annotes1(SAL_valid, __no)

#ifdef __cplusplus
#define _Notref_                   _SA_annotes0(SAL_notref)
#else
#define _Notref_
#endif

