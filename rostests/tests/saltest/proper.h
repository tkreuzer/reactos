#define _USE_ATTRIBUTES_FOR_SAL 0
#define _USE_DECLSPECS_FOR_SAL 1
#include <specstrings.h>

#include "proper.h"

int gach[3];

#if 0
void Test_scalar_In_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") long p1);
void Test_Out_bytecap_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_writableTo" "(" "byteCount(cb)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int *buffer, unsigned cb) { }
void Test_Out_cap_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_writableTo" "(" "elementCount(c)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int *buffer, unsigned c) { }
void Test_In_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") void* p1) { }
void Test_In_opt_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__maybe" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly")  void* p1) { }
void Test_In_bytecount_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_readableTo" "(" "byteCount(cb)" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") int *buffer, unsigned cb) { }
void Test_In_count_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_readableTo" "(" "elementCount(c)" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") int *buffer, unsigned c) { }
void Test_Deref_out_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_writableTo" "(" "elementCount(1)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { }
void Test_Deref_out_opt_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_writableTo" "(" "elementCount(1)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__maybe" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { *pp = gach; }
void Test_Deref_out_z_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_writableTo" "(" "elementCount(1)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_nullTerminated" "(" "__yes" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { *pp = gach; gach[1] = 0; }
void Test_In_z_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_nullTerminated" "(" "__yes" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") int *buffer) { }
void Test_Deref_post_valid_(__declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp){ }
#elif MS0
void Test_scalar_In_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") long p1);
void Test_Out_bytecap_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_writableTo" "(" "byteCount(cb)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int *buffer, unsigned cb) { }
void Test_Out_cap_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_writableTo" "(" "elementCount(c)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int *buffer, unsigned c) { }
void Test_In_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") void* p1) { }
void Test_In_opt_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__maybe" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly")  void* p1) { }
void Test_In_bytecount_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_readableTo" "(" "byteCount(cb)" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") int *buffer, unsigned cb) { }
void Test_In_count_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_readableTo" "(" "elementCount(c)" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") int *buffer, unsigned c) { }
void Test_Deref_out_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_writableTo" "(" "elementCount(1)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { }
void Test_Deref_out_opt_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_writableTo" "(" "elementCount(1)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__maybe" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { *pp = gach; }
void Test_Deref_out_z_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_writableTo" "(" "elementCount(1)" ")" ) __declspec("SAL_post") __declspec("SAL_valid") __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_nullTerminated" "(" "__yes" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { *pp = gach; gach[1] = 0; }
void Test_In_z_(__declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_pre") __declspec("SAL_nullTerminated" "(" "__yes" ")" ) __declspec("SAL_pre") __declspec("SAL_valid") __declspec("SAL_pre") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_readonly") int *buffer) { }
void Test_Deref_post_valid_(__declspec("SAL_post") __declspec("SAL_notref") __declspec("SAL_deref") __declspec("SAL_notref") __declspec("SAL_null" "(" "__no" ")" ) __declspec("SAL_post") __declspec("SAL_valid") int **pp) { }
#else
#define _In_ __in
#define _Out_bytecap_(x) __out_bcount(x)
#define _Out_cap_(x) __out_ecount(x)
#define _In_opt_ __in_opt
#define _In_bytecount_(x)
#define _In_count_(x) __in_ecount(x)
#define _Deref_out_ __deref_out
#define _Out_ __out
#define _Deref_out_z_ __deref_out_z
#define _In_z_ __in_z
#define _Deref_post_valid_
#define _Deref_out_opt_ __deref_out_opt
void Test_scalar_In_(_In_ long p1);
void Test_Out_bytecap_(_Out_bytecap_(cb) int *buffer, unsigned cb) { }
void Test_Out_cap_(_Out_cap_(c) int *buffer, unsigned c) { }
void Test_In_(_In_ void* p1) { }
void Test_In_opt_(_In_opt_  void* p1) { }
void Test_In_bytecount_(_In_bytecount_(cb) int *buffer, unsigned cb) { }
void Test_In_count_(_In_count_(c) int *buffer, unsigned c) { }
void Test_Deref_out_(_Deref_out_ int **pp) { }
void Test_Deref_out_opt_(_Deref_out_opt_ int **pp) { *pp = gach; }
void Test_Deref_out_z_(_Deref_out_z_ int **pp) { *pp = gach; gach[1] = 0; }
void Test_In_z_(_In_z_ int *buffer) { }
void Test_Deref_post_valid_(_Deref_post_valid_ int **pp) { }
#endif

void
main()
{
    long Long = 0;
    int Array[3];
    int *pInt = 0;

    Test_Out_bytecap_(Array, 12);
    Test_Out_cap_(Array, 3);

    Test_In_(&Long);
    Test_In_opt_(0);
    Test_In_opt_(&Long);
    Test_In_bytecount_(Array, 12);
    Test_In_count_(Array, 3);

    Test_Deref_out_(&pInt);
    Test_In_(pInt);
    Test_Deref_out_opt_(&pInt);
    Test_In_opt_(pInt);

    Test_Deref_out_z_(&pInt);
    Test_In_z_(pInt);

    pInt = 0;
    Test_Deref_post_valid_(&pInt);
    *pInt = 1;


}

#if 0
#define	__inner_exceptthat
#define	__inner_typefix(ctype)
#define	_Always_(annos)
#define	_At_(target, annos)
#define	_At_buffer_(target, iter, bound, annos)
#define	_Check_return_
#define	_COM_Outptr_
#define	_COM_Outptr_opt_
#define	_COM_Outptr_opt_result_maybenull_
#define	_COM_Outptr_result_maybenull_
#define	_Const_
#define	_Deref_in_bound_
#define	_Deref_in_range_(lb,ub)
#define	_Deref_inout_bound_
#define	_Deref_inout_z_
#define	_Deref_inout_z_bytecap_c_(size)
#define	_Deref_inout_z_cap_c_(size)
#define	_Deref_opt_out_
#define	_Deref_opt_out_opt_
#define	_Deref_opt_out_opt_z_
#define	_Deref_opt_out_z_
#define	_Deref_out_bound_
#define	_Deref_out_opt_z_
#define	_Deref_out_range_(lb,ub)
#define	_Deref_out_z_
#define	_Deref_out_z_bytecap_c_(size)
#define	_Deref_out_z_cap_c_(size)
#define	_Deref_post_bytecap_(size)
#define	_Deref_post_bytecap_c_(size)
#define	_Deref_post_bytecap_x_(size)
#define	_Deref_post_bytecount_(size)
#define	_Deref_post_bytecount_c_(size)
#define	_Deref_post_bytecount_x_(size)
#define	_Deref_post_cap_(size)
#define	_Deref_post_cap_c_(size)
#define	_Deref_post_cap_x_(size)
#define	_Deref_post_count_(size)
#define	_Deref_post_count_c_(size)
#define	_Deref_post_count_x_(size)
#define	_Deref_post_maybenull_
#define	_Deref_post_notnull_
#define	_Deref_post_null_
#define	_Deref_post_opt_bytecap_(size)
#define	_Deref_post_opt_bytecap_c_(size)
#define	_Deref_post_opt_bytecap_x_(size)
#define	_Deref_post_opt_bytecount_(size)
#define	_Deref_post_opt_bytecount_c_(size)
#define	_Deref_post_opt_bytecount_x_(size)
#define	_Deref_post_opt_cap_(size)
#define	_Deref_post_opt_cap_c_(size)
#define	_Deref_post_opt_cap_x_(size)
#define	_Deref_post_opt_count_(size)
#define	_Deref_post_opt_count_c_(size)
#define	_Deref_post_opt_count_x_(size)
#define	_Deref_post_opt_valid_
#define	_Deref_post_opt_valid_bytecap_(size)
#define	_Deref_post_opt_valid_bytecap_c_(size)
#define	_Deref_post_opt_valid_bytecap_x_(size)
#define	_Deref_post_opt_valid_cap_(size)
#define	_Deref_post_opt_valid_cap_c_(size)
#define	_Deref_post_opt_valid_cap_x_(size)
#define	_Deref_post_opt_z_
#define	_Deref_post_opt_z_bytecap_(size)
#define	_Deref_post_opt_z_bytecap_c_(size)
#define	_Deref_post_opt_z_bytecap_x_(size)
#define	_Deref_post_opt_z_cap_(size)
#define	_Deref_post_opt_z_cap_c_(size)
#define	_Deref_post_opt_z_cap_x_(size)
#define	_Deref_post_valid_bytecap_(size)
#define	_Deref_post_valid_bytecap_c_(size)
#define	_Deref_post_valid_bytecap_x_(size)
#define	_Deref_post_valid_cap_(size)
#define	_Deref_post_valid_cap_c_(size)
#define	_Deref_post_valid_cap_x_(size)
#define	_Deref_post_z_
#define	_Deref_post_z_bytecap_(size)
#define	_Deref_post_z_bytecap_c_(size)
#define	_Deref_post_z_bytecap_x_(size)
#define	_Deref_post_z_cap_(size)
#define	_Deref_post_z_cap_c_(size)
#define	_Deref_post_z_cap_x_(size)
#define	_Deref_pre_bytecap_(size)
#define	_Deref_pre_bytecap_c_(size)
#define	_Deref_pre_bytecap_x_(size)
#define	_Deref_pre_bytecount_(size)
#define	_Deref_pre_bytecount_c_(size)
#define	_Deref_pre_bytecount_x_(size)
#define	_Deref_pre_cap_(size)
#define	_Deref_pre_cap_c_(size)
#define	_Deref_pre_cap_x_(size)
#define	_Deref_pre_count_(size)
#define	_Deref_pre_count_c_(size)
#define	_Deref_pre_count_x_(size)
#define	_Deref_pre_invalid_
#define	_Deref_pre_maybenull_
#define	_Deref_pre_notnull_
#define	_Deref_pre_null_
#define	_Deref_pre_opt_bytecap_(size)
#define	_Deref_pre_opt_bytecap_c_(size)
#define	_Deref_pre_opt_bytecap_x_(size)
#define	_Deref_pre_opt_bytecount_(size)
#define	_Deref_pre_opt_bytecount_c_(size)
#define	_Deref_pre_opt_bytecount_x_(size)
#define	_Deref_pre_opt_cap_(size)
#define	_Deref_pre_opt_cap_c_(size)
#define	_Deref_pre_opt_cap_x_(size)
#define	_Deref_pre_opt_count_(size)
#define	_Deref_pre_opt_count_c_(size)
#define	_Deref_pre_opt_count_x_(size)
#define	_Deref_pre_opt_valid_
#define	_Deref_pre_opt_valid_bytecap_(size)
#define	_Deref_pre_opt_valid_bytecap_c_(size)
#define	_Deref_pre_opt_valid_bytecap_x_(size)
#define	_Deref_pre_opt_valid_cap_(size)
#define	_Deref_pre_opt_valid_cap_c_(size)
#define	_Deref_pre_opt_valid_cap_x_(size)
#define	_Deref_pre_opt_z_
#define	_Deref_pre_opt_z_bytecap_(size)
#define	_Deref_pre_opt_z_bytecap_c_(size)
#define	_Deref_pre_opt_z_bytecap_x_(size)
#define	_Deref_pre_opt_z_cap_(size)
#define	_Deref_pre_opt_z_cap_c_(size)
#define	_Deref_pre_opt_z_cap_x_(size)
#define	_Deref_pre_readonly_
#define	_Deref_pre_valid_
#define	_Deref_pre_valid_bytecap_(size)
#define	_Deref_pre_valid_bytecap_c_(size)
#define	_Deref_pre_valid_bytecap_x_(size)
#define	_Deref_pre_valid_cap_(size)
#define	_Deref_pre_valid_cap_c_(size)
#define	_Deref_pre_valid_cap_x_(size)
#define	_Deref_pre_writeonly_
#define	_Deref_pre_z_
#define	_Deref_pre_z_bytecap_(size)
#define	_Deref_pre_z_bytecap_c_(size)
#define	_Deref_pre_z_bytecap_x_(size)
#define	_Deref_pre_z_cap_(size)
#define	_Deref_pre_z_cap_c_(size)
#define	_Deref_pre_z_cap_x_(size)
#define	_Deref_prepost_bytecap_(size)
#define	_Deref_prepost_bytecap_x_(size)
#define	_Deref_prepost_bytecount_(size)
#define	_Deref_prepost_bytecount_x_(size)
#define	_Deref_prepost_cap_(size)
#define	_Deref_prepost_cap_x_(size)
#define	_Deref_prepost_count_(size)
#define	_Deref_prepost_count_x_(size)
#define	_Deref_prepost_opt_bytecap_(size)
#define	_Deref_prepost_opt_bytecap_x_(size)
#define	_Deref_prepost_opt_bytecount_(size)
#define	_Deref_prepost_opt_bytecount_x_(size)
#define	_Deref_prepost_opt_cap_(size)
#define	_Deref_prepost_opt_cap_x_(size)
#define	_Deref_prepost_opt_count_(size)
#define	_Deref_prepost_opt_count_x_(size)
#define	_Deref_prepost_opt_valid_
#define	_Deref_prepost_opt_valid_bytecap_(size)
#define	_Deref_prepost_opt_valid_bytecap_x_(size)
#define	_Deref_prepost_opt_valid_cap_(size)
#define	_Deref_prepost_opt_valid_cap_x_(size)
#define	_Deref_prepost_opt_z_
#define	_Deref_prepost_opt_z_bytecap_(size)
#define	_Deref_prepost_opt_z_cap_(size)
#define	_Deref_prepost_valid_
#define	_Deref_prepost_valid_bytecap_(size)
#define	_Deref_prepost_valid_bytecap_x_(size)
#define	_Deref_prepost_valid_cap_(size)
#define	_Deref_prepost_valid_cap_x_(size)
#define	_Deref_prepost_z_
#define	_Deref_prepost_z_bytecap_(size)
#define	_Deref_prepost_z_cap_(size)
#define	_Deref_ret_bound_
#define	_Deref_ret_opt_z_
#define	_Deref_ret_range_(lb,ub)
#define	_Deref_ret_z_
#define	_Deref2_pre_readonly_
#define	_Field_range_(min,max)
#define	_Field_size_(size)
#define	_Field_size_bytes_(size)
#define	_Field_size_bytes_full_(size)
#define	_Field_size_bytes_full_opt_(size)
#define	_Field_size_bytes_opt_(size)
#define	_Field_size_bytes_part_(size, count)
#define	_Field_size_bytes_part_opt_(size, count)
#define	_Field_size_full_(size)
#define	_Field_size_full_opt_(size)
#define	_Field_size_opt_(size)
#define	_Field_size_part_(size, count)
#define	_Field_size_part_opt_(size, count)
#define	_Field_z_
#define	_Group_(annos)
#define	_In_bound_
#define	_In_bytecount_c_(size)
#define	_In_bytecount_x_(size)
#define	_In_count_c_(size)
#define	_In_count_x_(size)
#define	_In_defensive_(annotes)
#define	_In_opt_bytecount_(size)
#define	_In_opt_bytecount_c_(size)
#define	_In_opt_bytecount_x_(size)
#define	_In_opt_count_(size)
#define	_In_opt_count_c_(size)
#define	_In_opt_count_x_(size)
#define	_In_opt_ptrdiff_count_(size)
#define	_In_opt_z_
#define	_In_opt_z_bytecount_(size)
#define	_In_opt_z_bytecount_c_(size)
#define	_In_opt_z_count_(size)
#define	_In_opt_z_count_c_(size)
#define	_In_ptrdiff_count_(size)
#define	_In_range_(lb,ub)
#define	_In_reads_(size)
#define	_In_reads_bytes_(size)
#define	_In_reads_bytes_opt_(size)
#define	_In_reads_opt_(size)
#define	_In_reads_opt_z_(size)
#define	_In_reads_or_z_(size)
#define	_In_reads_to_ptr_(ptr)
#define	_In_reads_to_ptr_opt_(ptr)
#define	_In_reads_to_ptr_opt_z_(ptr)
#define	_In_reads_to_ptr_z_(ptr)
#define	_In_reads_z_(size)
#define	_In_z_
#define	_In_z_bytecount_(size)
#define	_In_z_bytecount_c_(size)
#define	_In_z_count_(size)
#define	_In_z_count_c_(size)
#define	_Inout_
#define	_Inout_bytecap_(size)
#define	_Inout_bytecap_c_(size)
#define	_Inout_bytecap_x_(size)
#define	_Inout_bytecount_(size)
#define	_Inout_bytecount_c_(size)
#define	_Inout_bytecount_x_(size)
#define	_Inout_cap_(size)
#define	_Inout_cap_c_(size)
#define	_Inout_cap_x_(size)
#define	_Inout_count_(size)
#define	_Inout_count_c_(size)
#define	_Inout_count_x_(size)
#define	_Inout_defensive_(annotes)
#define	_Inout_opt_
#define	_Inout_opt_bytecap_(size)
#define	_Inout_opt_bytecap_c_(size)
#define	_Inout_opt_bytecap_x_(size)
#define	_Inout_opt_bytecount_(size)
#define	_Inout_opt_bytecount_c_(size)
#define	_Inout_opt_bytecount_x_(size)
#define	_Inout_opt_cap_(size)
#define	_Inout_opt_cap_c_(size)
#define	_Inout_opt_cap_x_(size)
#define	_Inout_opt_count_(size)
#define	_Inout_opt_count_c_(size)
#define	_Inout_opt_count_x_(size)
#define	_Inout_opt_ptrdiff_count_(size)
#define	_Inout_opt_z_
#define	_Inout_opt_z_bytecap_(size)
#define	_Inout_opt_z_bytecap_c_(size)
#define	_Inout_opt_z_bytecap_x_(size)
#define	_Inout_opt_z_bytecount_(size)
#define	_Inout_opt_z_bytecount_c_(size)
#define	_Inout_opt_z_cap_(size)
#define	_Inout_opt_z_cap_c_(size)
#define	_Inout_opt_z_cap_x_(size)
#define	_Inout_opt_z_count_(size)
#define	_Inout_opt_z_count_c_(size)
#define	_Inout_ptrdiff_count_(size)
#define	_Inout_updates_(size)
#define	_Inout_updates_all_(size)
#define	_Inout_updates_all_opt_(size)
#define	_Inout_updates_bytes_(size)
#define	_Inout_updates_bytes_all_(size)
#define	_Inout_updates_bytes_all_opt_(size)
#define	_Inout_updates_bytes_opt_(size)
#define	_Inout_updates_bytes_to_(size,count)
#define	_Inout_updates_bytes_to_opt_(size,count)
#define	_Inout_updates_opt_(size)
#define	_Inout_updates_opt_z_(size)
#define	_Inout_updates_to_(size,count)
#define	_Inout_updates_to_opt_(size,count)
#define	_Inout_updates_z_(size)
#define	_Inout_z_
#define	_Inout_z_bytecap_(size)
#define	_Inout_z_bytecap_c_(size)
#define	_Inout_z_bytecap_x_(size)
#define	_Inout_z_bytecount_(size)
#define	_Inout_z_bytecount_c_(size)
#define	_Inout_z_cap_(size)
#define	_Inout_z_cap_c_(size)
#define	_Inout_z_cap_x_(size)
#define	_Inout_z_count_(size)
#define	_Inout_z_count_c_(size)
#define	_Literal_
#define	_Maybenull_
#define	_Maybevalid_
#define	_Must_inspect_result_
#define	_Notliteral_
#define	_Notnull_
#define	_Notref_
#define	_Notvalid_
#define	_Null_
#define	_Null_terminated_
#define	_NullNull_terminated_
#define	_On_failure_(annos)
#define	_Out_
#define	_Out_bound_
#define	_Out_bytecap_c_(size)
#define	_Out_bytecap_post_bytecount_(cap,count)
#define	_Out_bytecap_x_(size)
#define	_Out_bytecapcount_(capcount)
#define	_Out_bytecapcount_x_(capcount)
#define	_Out_cap_c_(size)
#define	_Out_cap_m_(mult,size)
#define	_Out_cap_post_count_(cap,count)
#define	_Out_cap_x_(size)
#define	_Out_capcount_(capcount)
#define	_Out_capcount_x_(capcount)
#define	_Out_defensive_(annotes)
#define	_Out_opt_
#define	_Out_opt_bytecap_(size)
#define	_Out_opt_bytecap_c_(size)
#define	_Out_opt_bytecap_post_bytecount_(cap,count)
#define	_Out_opt_bytecap_x_(size)
#define	_Out_opt_bytecapcount_(capcount)
#define	_Out_opt_bytecapcount_x_(capcount)
#define	_Out_opt_cap_(size)
#define	_Out_opt_cap_c_(size)
#define	_Out_opt_cap_m_(mult,size)
#define	_Out_opt_cap_post_count_(cap,count)
#define	_Out_opt_cap_x_(size)
#define	_Out_opt_capcount_(capcount)
#define	_Out_opt_capcount_x_(capcount)
#define	_Out_opt_ptrdiff_cap_(size)
#define	_Out_opt_z_bytecap_(size)
#define	_Out_opt_z_bytecap_c_(size)
#define	_Out_opt_z_bytecap_post_bytecount_(cap,count)
#define	_Out_opt_z_bytecap_x_(size)
#define	_Out_opt_z_bytecapcount_(capcount)
#define	_Out_opt_z_cap_(size)
#define	_Out_opt_z_cap_c_(size)
#define	_Out_opt_z_cap_m_(mult,size)
#define	_Out_opt_z_cap_post_count_(cap,count)
#define	_Out_opt_z_cap_x_(size)
#define	_Out_opt_z_capcount_(capcount)
#define	_Out_ptrdiff_cap_(size)
#define	_Out_range_(lb,ub)
#define	_Out_writes_(size)
#define	_Out_writes_all_(size)
#define	_Out_writes_all_opt_(size)
#define	_Out_writes_bytes_(size)
#define	_Out_writes_bytes_all_(size)
#define	_Out_writes_bytes_all_opt_(size)
#define	_Out_writes_bytes_opt_(size)
#define	_Out_writes_bytes_to_(size,count)
#define	_Out_writes_bytes_to_opt_(size,count)
#define	_Out_writes_opt_(size)
#define	_Out_writes_opt_z_(size)
#define	_Out_writes_to_(size,count)
#define	_Out_writes_to_opt_(size,count)
#define	_Out_writes_to_ptr_(ptr)
#define	_Out_writes_to_ptr_opt_(ptr)
#define	_Out_writes_to_ptr_opt_z_(ptr)
#define	_Out_writes_to_ptr_z_(ptr)
#define	_Out_writes_z_(size)
#define	_Out_z_bytecap_(size)
#define	_Out_z_bytecap_c_(size)
#define	_Out_z_bytecap_post_bytecount_(cap,count)
#define	_Out_z_bytecap_x_(size)
#define	_Out_z_bytecapcount_(capcount)
#define	_Out_z_cap_(size)
#define	_Out_z_cap_c_(size)
#define	_Out_z_cap_m_(mult,size)
#define	_Out_z_cap_post_count_(cap,count)
#define	_Out_z_cap_x_(size)
#define	_Out_z_capcount_(capcount)
#define	_Outptr_
#define	_Outptr_opt_
#define	_Outptr_opt_result_buffer_(size)
#define	_Outptr_opt_result_buffer_all_(size)
#define	_Outptr_opt_result_buffer_all_maybenull_(size)
#define	_Outptr_opt_result_buffer_maybenull_(size)
#define	_Outptr_opt_result_buffer_to_(size, count)
#define	_Outptr_opt_result_buffer_to_maybenull_(size, count)
#define	_Outptr_opt_result_bytebuffer_(size)
#define	_Outptr_opt_result_bytebuffer_all_(size)
#define	_Outptr_opt_result_bytebuffer_all_maybenull_(size)
#define	_Outptr_opt_result_bytebuffer_maybenull_(size)
#define	_Outptr_opt_result_bytebuffer_to_(size, count)
#define	_Outptr_opt_result_bytebuffer_to_maybenull_(size, count)
#define	_Outptr_opt_result_maybenull_
#define	_Outptr_opt_result_maybenull_z_
#define	_Outptr_opt_result_nullonfailure_
#define	_Outptr_opt_result_z_
#define	_Outptr_result_buffer_(size)
#define	_Outptr_result_buffer_all_(size)
#define	_Outptr_result_buffer_all_maybenull_(size)
#define	_Outptr_result_buffer_maybenull_(size)
#define	_Outptr_result_buffer_to_(size, count)
#define	_Outptr_result_buffer_to_maybenull_(size, count)
#define	_Outptr_result_bytebuffer_(size)
#define	_Outptr_result_bytebuffer_all_(size)
#define	_Outptr_result_bytebuffer_all_maybenull_(size)
#define	_Outptr_result_bytebuffer_maybenull_(size)
#define	_Outptr_result_bytebuffer_to_(size, count)
#define	_Outptr_result_bytebuffer_to_maybenull_(size, count)
#define	_Outptr_result_maybenull_
#define	_Outptr_result_maybenull_z_
#define	_Outptr_result_nullonfailure_
#define	_Outptr_result_z_
#define	_Outref_
#define	_Outref_result_buffer_(size)
#define	_Outref_result_buffer_all_(size)
#define	_Outref_result_buffer_all_maybenull_(size)
#define	_Outref_result_buffer_maybenull_(size)
#define	_Outref_result_buffer_to_(size, count)
#define	_Outref_result_buffer_to_maybenull_(size, count)
#define	_Outref_result_bytebuffer_(size)
#define	_Outref_result_bytebuffer_all_(size)
#define	_Outref_result_bytebuffer_all_maybenull_(size)
#define	_Outref_result_bytebuffer_maybenull_(size)
#define	_Outref_result_bytebuffer_to_(size, count)
#define	_Outref_result_bytebuffer_to_maybenull_(size, count)
#define	_Outref_result_maybenull_
#define	_Outref_result_nullonfailure_
#define	_Points_to_data_
#define	_Post_
#define	_Post_bytecap_(size)
#define	_Post_bytecount_(size)
#define	_Post_bytecount_c_(size)
#define	_Post_bytecount_x_(size)
#define	_Post_cap_(size)
#define	_Post_count_(size)
#define	_Post_count_c_(size)
#define	_Post_count_x_(size)
#define	_Post_defensive_
#define	_Post_equal_to_(expr)
#define	_Post_invalid_
#define	_Post_maybenull_
#define	_Post_maybez_
#define	_Post_notnull_
#define	_Post_null_
#define	_Post_ptr_invalid_
#define	_Post_readable_byte_size_(size)
#define	_Post_readable_size_(size)
#define	_Post_satisfies_(cond)
#define	_Post_valid_
#define	_Post_writable_byte_size_(size)
#define	_Post_writable_size_(size)
#define	_Post_z_
#define	_Post_z_bytecount_(size)
#define	_Post_z_bytecount_c_(size)
#define	_Post_z_bytecount_x_(size)
#define	_Post_z_count_(size)
#define	_Post_z_count_c_(size)
#define	_Post_z_count_x_(size)
#define	_Pre_
#define	_Pre_bytecap_(size)
#define	_Pre_bytecap_c_(size)
#define	_Pre_bytecap_x_(size)
#define	_Pre_bytecount_(size)
#define	_Pre_bytecount_c_(size)
#define	_Pre_bytecount_x_(size)
#define	_Pre_cap_(size)
#define	_Pre_cap_c_(size)
#define	_Pre_cap_c_one_
#define	_Pre_cap_for_(param)
#define	_Pre_cap_m_(mult,size)
#define	_Pre_cap_x_(size)
#define	_Pre_count_(size)
#define	_Pre_count_c_(size)
#define	_Pre_count_x_(size)
#define	_Pre_defensive_
#define	_Pre_equal_to_(expr)
#define	_Pre_invalid_
#define	_Pre_maybenull_
#define	_Pre_notnull_
#define	_Pre_null_
#define	_Pre_opt_bytecap_(size)
#define	_Pre_opt_bytecap_c_(size)
#define	_Pre_opt_bytecap_x_(size)
#define	_Pre_opt_bytecount_(size)
#define	_Pre_opt_bytecount_c_(size)
#define	_Pre_opt_bytecount_x_(size)
#define	_Pre_opt_cap_(size)
#define	_Pre_opt_cap_c_(size)
#define	_Pre_opt_cap_c_one_
#define	_Pre_opt_cap_for_(param)
#define	_Pre_opt_cap_m_(mult,size)
#define	_Pre_opt_cap_x_(size)
#define	_Pre_opt_count_(size)
#define	_Pre_opt_count_c_(size)
#define	_Pre_opt_count_x_(size)
#define	_Pre_opt_ptrdiff_cap_(ptr)
#define	_Pre_opt_ptrdiff_count_(ptr)
#define	_Pre_opt_valid_
#define	_Pre_opt_valid_bytecap_(size)
#define	_Pre_opt_valid_bytecap_c_(size)
#define	_Pre_opt_valid_bytecap_x_(size)
#define	_Pre_opt_valid_cap_(size)
#define	_Pre_opt_valid_cap_c_(size)
#define	_Pre_opt_valid_cap_x_(size)
#define	_Pre_opt_z_
#define	_Pre_opt_z_bytecap_(size)
#define	_Pre_opt_z_bytecap_c_(size)
#define	_Pre_opt_z_bytecap_x_(size)
#define	_Pre_opt_z_cap_(size)
#define	_Pre_opt_z_cap_c_(size)
#define	_Pre_opt_z_cap_x_(size)
#define	_Pre_ptrdiff_cap_(ptr)
#define	_Pre_ptrdiff_count_(ptr)
#define	_Pre_readable_byte_size_(size)
#define	_Pre_readable_size_(size)
#define	_Pre_readonly_
#define	_Pre_satisfies_(cond)
#define	_Pre_valid_
#define	_Pre_valid_bytecap_(size)
#define	_Pre_valid_bytecap_c_(size)
#define	_Pre_valid_bytecap_x_(size)
#define	_Pre_valid_cap_(size)
#define	_Pre_valid_cap_c_(size)
#define	_Pre_valid_cap_x_(size)
#define	_Pre_writable_byte_size_(size)
#define	_Pre_writable_size_(size)
#define	_Pre_writeonly_
#define	_Pre_z_
#define	_Pre_z_bytecap_(size)
#define	_Pre_z_bytecap_c_(size)
#define	_Pre_z_bytecap_x_(size)
#define	_Pre_z_cap_(size)
#define	_Pre_z_cap_c_(size)
#define	_Pre_z_cap_x_(size)
#define	_Prepost_bytecount_(size)
#define	_Prepost_bytecount_c_(size)
#define	_Prepost_bytecount_x_(size)
#define	_Prepost_count_(size)
#define	_Prepost_count_c_(size)
#define	_Prepost_count_x_(size)
#define	_Prepost_opt_bytecount_(size)
#define	_Prepost_opt_bytecount_c_(size)
#define	_Prepost_opt_bytecount_x_(size)
#define	_Prepost_opt_count_(size)
#define	_Prepost_opt_count_c_(size)
#define	_Prepost_opt_count_x_(size)
#define	_Prepost_opt_valid_
#define	_Prepost_opt_z_
#define	_Prepost_valid_
#define	_Prepost_z_
#define	_Printf_format_string_
#define	_Readable_bytes_(size)
#define	_Readable_elements_(size)
#define	_Reserved_
#define	_Result_nullonfailure_
#define	_Result_zeroonfailure_
#define	_Ret_
#define	_Ret_bound_
#define	_Ret_bytecap_(size)
#define	_Ret_bytecap_c_(size)
#define	_Ret_bytecap_x_(size)
#define	_Ret_bytecount_(size)
#define	_Ret_bytecount_c_(size)
#define	_Ret_bytecount_x_(size)
#define	_Ret_cap_(size)
#define	_Ret_cap_c_(size)
#define	_Ret_cap_x_(size)
#define	_Ret_count_(size)
#define	_Ret_count_c_(size)
#define	_Ret_count_x_(size)
#define	_Ret_maybenull_
#define	_Ret_maybenull_z_
#define	_Ret_notnull_
#define	_Ret_null_
#define	_Ret_opt_
#define	_Ret_opt_bytecap_(size)
#define	_Ret_opt_bytecap_c_(size)
#define	_Ret_opt_bytecap_x_(size)
#define	_Ret_opt_bytecount_(size)
#define	_Ret_opt_bytecount_c_(size)
#define	_Ret_opt_bytecount_x_(size)
#define	_Ret_opt_cap_(size)
#define	_Ret_opt_cap_c_(size)
#define	_Ret_opt_cap_x_(size)
#define	_Ret_opt_count_(size)
#define	_Ret_opt_count_c_(size)
#define	_Ret_opt_count_x_(size)
#define	_Ret_opt_valid_
#define	_Ret_opt_z_
#define	_Ret_opt_z_bytecap_(size)
#define	_Ret_opt_z_bytecount_(size)
#define	_Ret_opt_z_cap_(size)
#define	_Ret_opt_z_count_(size)
#define	_Ret_range_(lb,ub)
#define	_Ret_valid_
#define	_Ret_writes_(size)
#define	_Ret_writes_bytes_(size)
#define	_Ret_writes_bytes_maybenull_(size)
#define	_Ret_writes_bytes_to_(size,count)
#define	_Ret_writes_bytes_to_maybenull_(size,count)
#define	_Ret_writes_maybenull_(size)
#define	_Ret_writes_maybenull_z_(size)
#define	_Ret_writes_to_(size,count)
#define	_Ret_writes_to_maybenull_(size,count)
#define	_Ret_writes_z_(size)
#define	_Ret_z_
#define	_Ret_z_bytecap_(size)
#define	_Ret_z_bytecount_(size)
#define	_Ret_z_cap_(size)
#define	_Ret_z_count_(size)
#define	_Return_type_success_(expr)
#define	_Scanf_format_string_
#define	_Scanf_s_format_string_
#define	_Struct_size_bytes_(size)
#define	_Success_(expr)
#define	_Unchanged_(e)
#define	_Use_decl_annotations_
#define	_Valid_
#define	_When_(expr, annos)
#define	_Writable_bytes_(size)
#define	_Writable_elements_(size)


#endif

