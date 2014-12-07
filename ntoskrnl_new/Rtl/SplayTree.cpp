
#include "SplayTree.hpp"

extern "C" {

PRTL_SPLAY_LINKS
NTAPI
RtlSplay (
    _Inout_ PRTL_SPLAY_LINKS Links)
{
    __debugbreak();
    return NULL;
}

PRTL_SPLAY_LINKS
NTAPI
RtlDelete (
    _In_ PRTL_SPLAY_LINKS Links)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
RtlDeleteNoSplay (
    _In_ PRTL_SPLAY_LINKS Links,
    _Inout_ PRTL_SPLAY_LINKS *Root)
{
    __debugbreak();
}

_Must_inspect_result_
PRTL_SPLAY_LINKS
NTAPI
RtlRealPredecessor (
    _In_ PRTL_SPLAY_LINKS Links)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PRTL_SPLAY_LINKS
NTAPI
RtlRealSuccessor (
    _In_ PRTL_SPLAY_LINKS Links)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PRTL_SPLAY_LINKS
NTAPI
RtlSubtreePredecessor (
    _In_ PRTL_SPLAY_LINKS Links)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
PRTL_SPLAY_LINKS
NTAPI
RtlSubtreeSuccessor (
    _In_ PRTL_SPLAY_LINKS Links)
{
    __debugbreak();
    return NULL;
}

} // extern "C"
