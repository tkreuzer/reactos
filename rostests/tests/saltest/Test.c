
#include <SpecStrings.h>

void Test_scalar_In_(__in int i) { }

void Test__out(__out int ** ppi)
{
}

void Test_Pre_invalid_(__pre __notvalid int **p)
{
	//**p = 0; // <- This will fail
	//*p = 0; // <- This will fail
}

//void Test_Deref_post_valid_(_Deref_post_valid_ int **pp)
//{
//	//*pp = 0; // <- This fails
//	*pp = &globalInt; /* <- This is needed! */
//}

//


void Test_Out_(__out int** ppi) { *ppi = 0; }


typedef
void FN_Test(__in void *pv);

FN_Test Test_In_;

void Test_In_(void *pv)
{
    *(int*)pv = 1;
}

void
main()
{
    int x = 0;
    Test_In_(&x);


}

