
#define _SA_annotes0(n)                [SAL_annotes(Name=#n)]
#define _SA_annotes1(n,pp1)            [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1))]
#define _SA_annotes2(n,pp1,pp2)        [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1), p2=_SA_SPECSTRIZE(pp2))]
#define _SA_annotes3(n,pp1,pp2,pp3)    [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1), p2=_SA_SPECSTRIZE(pp2), p3=_SA_SPECSTRIZE(pp3))]

#define _Pre_invalid_                   _Deref_pre1_impl_(__notvalid_impl)
#define _Deref_pre_invalid_             [SA_Pre(Deref=1,Valid=SA_No)]

