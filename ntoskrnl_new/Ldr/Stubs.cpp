
#include <ntoskrnl.h>

extern "C" {


@ stdcall LdrAccessResource(ptr ptr ptr ptr)
@ stdcall LdrEnumResources(ptr ptr long ptr ptr)
@ stdcall LdrFindResourceDirectory_U(ptr ptr long ptr)
@ stub LdrFindResourceEx_U
@ stdcall LdrFindResource_U(ptr ptr long ptr)
@ stub LdrResFindResource
@ stub LdrResFindResourceDirectory
@ stub LdrResSearchResource



}; // extern "C"
