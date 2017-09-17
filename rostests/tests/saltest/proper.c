//#define _USE_DECLSPECS_FOR_SAL 1
//#define _USE_ATTRIBUTES_FOR_SAL 0

#include <SpecStrings.h>

//#ifdef _PREFAST_
//#include "_new.h"
//#else
//#include "_new_dummy.h"
//#endif
//#include "_old.h"

int globalInt = 0;

void Test_Null_(void *pv) { }
void Test_Pre_null_(_Pre_null_ void *pv) { }
void Test_Post_null_(void *pv) { if (pv) __debugbreak(); }
void Test_Post_null_(_Post_null_ void *pv);
void Test_Deref_post_null_(_Deref_post_null_ void **ppv) { *ppv = 0; }

void Test_Notnull_(_Notnull_ void* pv) { *(int*)pv = 0; }

void Test_Maybenull_(_Maybenull_ int*p1) { if (p1) *p1 = 0; }

void Test_Valid_(_Valid_ int*p1) { *p1 = 0; }
void Test_Pre_valid_(_Pre_valid_ void *pv) { }
void Test_Post_valid_(_Post_valid_ int *p) { }

void Test_Notvalid_(_Notvalid_ void *pv)
{
    //*(int*)pv = 1; // <- This fails!
}
void Test_Pre_invalid_(_Pre_invalid_ int **p)
{
	//**p = 0; // <- This will fail
	*p = 0; // <- This should fail
}

void Test_Deref_post_valid_(_Deref_post_valid_ int **pp)
{
	//*pp = 0; // <- This fails
	*pp = &globalInt; /* <- This is needed! */
}

void Test_scalar_In_(_In_ int i) { }

#if 1

void Test_Deref_pre_invalid_(_Deref_pre_invalid_ int **pp)
{
    //*pp = &globalInt;
    //**pp = 1;
}

#else

#ifdef _PREFAST_
void Test_Deref_pre_invalid_(
    _Deref_pre_invalid_
    int **pp)
#else
void Test_Deref_pre_invalid_(int **pp)
#endif
{
    //*pp = &globalInt;
    //**pp = 1;
}

//void Test_Deref_out_opt_(_Deref_out_opt_ int **pp) { *pp = 0; }
#endif



void Test_Out_(__out int** ppi) { **ppi = 0; }
//void Test__out(__out int** ppi) { *ppi = 0; }

void Test_Pre_maybenull_(_Pre_maybenull_ void *pv) { }

void Test_Pre_opt_valid_(_Pre_opt_valid_ void *pv) { }

void Test_Pre_opt_valid_bytecap_(_Pre_opt_valid_bytecap_(2) void *pv) { }

void Test_Deref_pre_maybenull_(_Deref_pre_maybenull_ int **ppi);

void Test_Prepost_opt_bytecount_(_Prepost_opt_bytecount_(4) void *pv) { }

void Test_Deref_prepost_opt_bytecap_(_Deref_prepost_opt_bytecap_(4) void **pv) { }

void Test_Out_opt_(_Out_opt_ void *pv) { }

void Test_Deref_opt_out_(_Deref_opt_out_ void **ppv) { }

void Test_Deref_out_opt_(_Deref_out_opt_ void **ppv) { }

void Test_Writable_bytes_(_Writable_bytes_(10) char *pstr) { }

_Ret_opt_valid_ int * Test_Ret_opt_valid_(void) { return 0; }

typedef struct _UNICODE_STRING
{
    unsigned short Length;
    unsigned short MaximumLength;
    unsigned short *Buffer;
} UNICODE_STRING, *PUNICODE_STRING;


#define _String_length_(String)  _When_(String[0] == 0, 0) _When_(String[0] != 0, 1 + _String_length_(String + 1))

_IRQL_requires_max_(2)
_At_(DestinationString->Buffer, _Post_equal_to_(SourceString))
_At_(SourceString, _Pre_equal_to_(0))
//_At_(DestinationString->Length, _Post_equal_to_(_String_length_(SourceString) * sizeof(short)))
//_At_(DestinationString->MaximumLength, _Post_equal_to_(DestinationString->Length + sizeof(short)))
void
RtlInitUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem const unsigned short * SourceString)
{
    _At_(SourceString, _Pre_satisfies_(SourceString != 0)) char a = a = 0;

}

void xxxx()
{
    UNICODE_STRING mystring;
    RtlInitUnicodeString(&mystring, 0);
}

#if 0
_Success_(1)
_Unchanged_(Destination->MaximumLength)
_Unchanged_(Destination->Buffer)
_When_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(short) <= Destination->MaximumLength,
    _At_(Destination->Length,
         _Post_equal_to_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(short)))
    _At_(return, _Out_range_(==, 0)))
_When_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(short) > Destination->MaximumLength,
    _Unchanged_(Destination->Length)
    _At_(return, _Out_range_(<, 0)))
long
RtlAppendUnicodeToString (
    _Inout_ PUNICODE_STRING Destination,
    _In_opt_z_ PCWSTR Source
    )
{
}
#endif

void
main()
{
    int val;

    Test_Notnull_(&val);
    Test_Maybenull_(&val);
    Test_Maybenull_(0);
    Test_Notvalid_(&val);
    Test_Pre_null_(0);

    val = 1;
    Test_Notvalid_(&val);

    {
        int val1;
        // Test_Pre_valid_(&val1); // <- must fail!
        Test_Post_valid_(&val1);
        Test_Pre_valid_(&val1);
        Test_Notvalid_(&val1);
    }

    {
        int *pval1;
        Test_Pre_invalid_(&pval1);

        Test_Deref_post_valid_(&pval1);
        Test_Pre_valid_(pval1);
        Test_Post_null_(pval1);
        //Test_Pre_null_(pval1); // <- must fail!
		Test_Deref_post_null_(&pval1);
		Test_Pre_null_(pval1);
		Test_Pre_invalid_(&pval1);
    }

    {
        int *pval1;
        Test_Out_(&pval1);
        //Test_Pre_valid_(&pval1);
    }

    Test_Pre_maybenull_(0);
    Test_Pre_opt_valid_(0);
    Test_Pre_opt_valid_bytecap_(0);
    Test_Prepost_opt_bytecount_(0);
    Test_Deref_prepost_opt_bytecap_(0);
    Test_Out_opt_(0);
    Test_Writable_bytes_(0);

    {
        int *pi = 0;
        Test_Deref_pre_maybenull_(&pi);
    }

    {
        void *pv;
        Test_Deref_opt_out_(0);
        Test_Deref_opt_out_(&pv);
        Test_Pre_valid_(pv);
        Test_Notnull_(pv);
    }

    {
        void *pv;
        Test_Deref_out_opt_(&pv);
        //Test_Pre_valid_(pv); // fails
        //Test_Notnull_(pv); // fails
    }

    {
        void *pv;
        pv = Test_Ret_opt_valid_();
        if (pv) Test_Pre_valid_(pv);
        if (pv) Test_Notnull_(pv);
    }

    {
        //void *pv;
        //Test_Outptr_result_bytebuffer_(&pv);
    }

}


