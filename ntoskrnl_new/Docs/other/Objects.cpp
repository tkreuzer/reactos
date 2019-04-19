
typedef struct _HPROCESS *HPROCESS;

namespace Ps {

class PROCESS
{
    HPROCESS _ProcessHandle;
    struct _EPROCESS *_Process;

public:

    PROCESS (
        HPROCESS ProcessHandle) :
            _ProcessHandle(ProcessHandle),
            _Process(ProcessHandle == NtCurrenProcess() ? PsGetCurrentProcess : NULL)
    {
    }

};

class CURRENT_PROCESS : public PROCESS
{

public:

    CURRENT_PROCESS (
        VOID) :
            PROCESS(NtCurrentProcess())
    {
    }

    HANDLE
    GetHandle ()
    {
        return NtCurrentProcess();
    }

};

CURRENT_PROCESS CurrentProcess;

} // namespace Ps

VOID
TestFunction2 (
    Ps::PROCESS &Process)
{

}

VOID
TestFunction (
    HPROCESS ProcessHandle)
{
    Ps::PROCESS process(ProcessHandle);


}
