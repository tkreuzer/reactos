
#include "Rtl.hpp"
#include "Sid.hpp"

extern "C" {

// undocumented
// see also GetAppContainerNamedObjectPath (securityappcontainer.h)
NTSTATUS
NTAPI
RtlGetAppContainerNamedObjectPath (
    _In_opt_ HANDLE Token,
    _In_opt_ PSID AppContainerSid,
    _In_ BOOLEAN P3,
    _Out_ PUNICODE_STRING Path)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

//@ stub RtlGetAppContainerParent
//@ stub RtlGetAppContainerSidType

} // extern "C"
