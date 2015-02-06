
#include "Obp.hpp"

extern "C"
ULONG
NTAPI
ObGetProcessHandleCount(
    IN PEPROCESS Process)
{
    //Ps::PPROCESS ProcessObject = reinterpret_cast<Ps::PPROCESS>(Process);
    //HandleTable = ProcessObject->GetHandleTable();
    //return HandleTable ? HandleTable->GetHandleCount() : 0;
    __debugbreak();
    return 0;
}

extern "C"
NTSTATUS
NTAPI
ObInitProcess(
    IN PEPROCESS Parent OPTIONAL,
    IN PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
VOID
NTAPI
ObKillProcess(
    IN PEPROCESS Process)
{
    __debugbreak();
}

extern "C"
VOID
NTAPI
ObClearProcessHandleTable(
    IN PEPROCESS Process)
{
    __debugbreak();
}
