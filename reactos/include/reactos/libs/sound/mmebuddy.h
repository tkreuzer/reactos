/*
 * PROJECT:     ReactOS Sound System "MME Buddy" Library
 * LICENSE:     GPL - See COPYING in the top level directory
 * FILE:        include/reactos/libs/sound/mmebuddy.h
 *
 * PURPOSE:     Header for the "MME Buddy" helper library (located in
 *              lib/drivers/sound/mmebuddy)
 *
 * PROGRAMMERS: Andrew Greenwood (silverblade@reactos.org)
 *
 * HISTORY:     4 July 2008 - Created
 *              31 Dec 2008 - Split off NT4-specific code into a separate library
 *
 * NOTES:       MME Buddy was the best name I could come up with...
 *              The structures etc. here should be treated as internal to the
 *              library so should not be directly accessed elsewhere. Perhaps they
 *              can be moved to an internal header?
*/

#ifndef ROS_AUDIO_MMEBUDDY_H
#define ROS_AUDIO_MMEBUDDY_H

/*
    Hacky debug macro
*/

#define POPUP(...) \
    { \
        WCHAR dbg_popup_msg[1024], dbg_popup_title[256]; \
        wsprintf(dbg_popup_title, L"%hS(%d)", __FILE__, __LINE__); \
        wsprintf(dbg_popup_msg, __VA_ARGS__); \
        MessageBox(0, dbg_popup_msg, dbg_popup_title, MB_OK | MB_TASKMODAL); \
    }

#ifndef NDEBUG
    #define SND_ERR(...) \
        { \
            WCHAR dbg_popup_msg[1024]; \
            wsprintf(dbg_popup_msg, __VA_ARGS__); \
            OutputDebugString(dbg_popup_msg); \
        }
    #define SND_WARN(...) \
        { \
            WCHAR dbg_popup_msg[1024]; \
            wsprintf(dbg_popup_msg, __VA_ARGS__); \
            OutputDebugString(dbg_popup_msg); \
        }
    #define SND_TRACE(...) \
        { \
            WCHAR dbg_popup_msg[1024]; \
            wsprintf(dbg_popup_msg, __VA_ARGS__); \
            OutputDebugString(dbg_popup_msg); \
        }

    #define SND_ASSERT(condition) \
        { \
            if ( ! ( condition ) ) \
            { \
                SND_ERR(L"ASSERT FAILED: %hS File %hS Line %u\n", #condition, __FILE__, __LINE__); \
                POPUP(L"ASSERT FAILED: %hS\n", #condition); \
                ExitProcess(1); \
            } \
        }

    #define DUMP_WAVEHDR_QUEUE(sound_device_instance) \
        { \
            PWAVEHDR CurrDumpHdr = sound_device_instance->HeadWaveHeader; \
            SND_TRACE(L"-- Current wave header list --\n"); \
            while ( CurrDumpHdr ) \
            { \
                SND_TRACE(L"%x | %d bytes | flags: %x\n", CurrDumpHdr->lpData, \
                          CurrDumpHdr->dwBufferLength, \
                          CurrDumpHdr->dwFlags); \
                CurrDumpHdr = CurrDumpHdr->lpNext; \
            } \
        }

#else
    #define SND_ERR(...) do {} while ( 0 )
    #define SND_WARN(...) do {} while ( 0 )
    #define SND_TRACE(...) do {} while ( 0 )
    #define SND_ASSERT(condition) do {} while ( 0 )
    #define DUMP_WAVEHDR_QUEUE(condition) do {} while ( 0 )
#endif

/*
    Some memory allocation helper macros
*/

#define AllocateStruct(thing) \
    (thing*) AllocateMemory(sizeof(thing))

#define StringLengthToBytes(chartype, string_length) \
    ( ( string_length + 1 ) * sizeof(chartype) )

#define AllocateWideString(string_length) \
    (PWSTR) AllocateMemory(StringLengthToBytes(WCHAR, string_length))

#define ZeroWideString(string) \
    ZeroMemory(string, StringLengthToBytes(WCHAR, wcslen(string)))

#define CopyWideString(dest, source) \
    CopyMemory(dest, source, StringLengthToBytes(WCHAR, wcslen(source)))


/*
    Helps find the minimum/maximum of two values
*/

#define MinimumOf(value_a, value_b) \
    ( value_a < value_b ? value_a : value_b )

#define MaximumOf(value_a, value_b) \
    ( value_a > value_b ? value_a : value_b )


/*
    Convert a device type into a zero-based array index
*/

#define SOUND_DEVICE_TYPE_TO_INDEX(x) \
    ( x - MIN_SOUND_DEVICE_TYPE )

#define INDEX_TO_SOUND_DEVICE_TYPE(x) \
    ( x + MIN_SOUND_DEVICE_TYPE )


/*
    Validation
*/

#define IsValidSoundDeviceType IS_VALID_SOUND_DEVICE_TYPE

#define VALIDATE_MMSYS_PARAMETER(parameter_condition) \
    { \
        if ( ! (parameter_condition) ) \
        { \
            SND_ERR(L"FAILED parameter check: %hS\n", #parameter_condition); \
            return MMSYSERR_INVALPARAM; \
        } \
    }

#define MMSUCCESS(result) \
    ( result == MMSYSERR_NOERROR )


/*
    Types and Structures
*/

typedef UCHAR MMDEVICE_TYPE, *PMMDEVICE_TYPE;
struct _SOUND_DEVICE;
struct _SOUND_DEVICE_INSTANCE;


#define DEFINE_GETCAPS_FUNCTYPE(func_typename, caps_type) \
    typedef MMRESULT (*func_typename)( \
        IN  struct _SOUND_DEVICE* SoundDevice, \
        IN  DWORD DeviceId, \
        OUT caps_type Capabilities, \
        IN  DWORD CapabilitiesSize);

/* This one is for those of us who don't care */
DEFINE_GETCAPS_FUNCTYPE(MMGETCAPS_FUNC, DWORD_PTR);

/* These are for those of us that do */
DEFINE_GETCAPS_FUNCTYPE(MMGETWAVEOUTCAPS_FUNC, LPWAVEOUTCAPS);
DEFINE_GETCAPS_FUNCTYPE(MMGETWAVEINCAPS_FUNC,  LPWAVEINCAPS );
DEFINE_GETCAPS_FUNCTYPE(MMGETMIDIOUTCAPS_FUNC, LPMIDIOUTCAPS);
DEFINE_GETCAPS_FUNCTYPE(MMGETMIDIINCAPS_FUNC,  LPMIDIINCAPS );

struct _SOUND_DEVICE;
struct _SOUND_DEVICE_INSTANCE;


/*
    By extending the OVERLAPPED structure, it becomes possible to provide the
    I/O completion routines with additional information.
*/

typedef struct _SOUND_OVERLAPPED
{
    OVERLAPPED Standard;
    struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance;
    PWAVEHDR Header;
    BOOL PerformCompletion;

    DWORD OriginalBufferSize;
    LPOVERLAPPED_COMPLETION_ROUTINE OriginalCompletionRoutine;

} SOUND_OVERLAPPED, *PSOUND_OVERLAPPED;

typedef MMRESULT (*WAVE_COMMIT_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  PVOID OffsetPtr,
    IN  DWORD Bytes,
    IN  PSOUND_OVERLAPPED Overlap,
    IN  LPOVERLAPPED_COMPLETION_ROUTINE CompletionRoutine);

typedef MMRESULT (*MMMIXERQUERY_FUNC) (
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN UINT uMsg,
    IN LPVOID Parameter,
    IN DWORD Flags);


typedef MMRESULT (*MMWAVEQUERYFORMATSUPPORT_FUNC)(
    IN  struct _SOUND_DEVICE* Device,
    IN  PWAVEFORMATEX WaveFormat,
    IN  DWORD WaveFormatSize);

typedef MMRESULT (*MMWAVESETFORMAT_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* Instance,
    IN  DWORD DeviceId,
    IN  PWAVEFORMATEX WaveFormat,
    IN  DWORD WaveFormatSize);

typedef MMRESULT (*MMOPEN_FUNC)(
    IN  struct _SOUND_DEVICE* SoundDevice,
    OUT PVOID* Handle);

typedef MMRESULT (*MMCLOSE_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  PVOID Handle);  /* not sure about this */

typedef MMRESULT (*MMWAVEHEADER_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  PWAVEHDR WaveHeader);

typedef MMRESULT (*MMBUFFER_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  PVOID Buffer,
    IN  DWORD Length);

typedef MMRESULT(*MMGETPOS_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  MMTIME* Time);


typedef MMRESULT(*MMSETSTATE_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  BOOL bStart);


typedef MMRESULT(*MMQUERYDEVICEINTERFACESTRING_FUNC)(
    IN  MMDEVICE_TYPE DeviceType,
    IN  DWORD DeviceId,
    IN  LPWSTR Interface,
    IN  DWORD  InterfaceLength,
    OUT  DWORD * InterfaceSize);

typedef MMRESULT(*MMRESETSTREAM_FUNC)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  MMDEVICE_TYPE DeviceType,
    IN  BOOLEAN bStartReset);

typedef struct _MMFUNCTION_TABLE
{
    union
    {
        MMGETCAPS_FUNC              GetCapabilities;
        MMGETWAVEOUTCAPS_FUNC       GetWaveOutCapabilities;
        MMGETWAVEINCAPS_FUNC        GetWaveInCapabilities;
        MMGETMIDIOUTCAPS_FUNC       GetMidiOutCapabilities;
        MMGETMIDIINCAPS_FUNC        GetMidiInCapabilities;
    };

    MMOPEN_FUNC                     Open;
    MMCLOSE_FUNC                    Close;

    MMWAVEQUERYFORMATSUPPORT_FUNC   QueryWaveFormatSupport;
    MMWAVESETFORMAT_FUNC            SetWaveFormat;

    MMMIXERQUERY_FUNC               QueryMixerInfo;

    WAVE_COMMIT_FUNC                CommitWaveBuffer;

    MMGETPOS_FUNC                   GetPos;
    MMSETSTATE_FUNC                 SetState;
    MMQUERYDEVICEINTERFACESTRING_FUNC     GetDeviceInterfaceString;
    MMRESETSTREAM_FUNC               ResetStream;

    // Redundant
    //MMWAVEHEADER_FUNC               PrepareWaveHeader;
    //MMWAVEHEADER_FUNC               UnprepareWaveHeader;
    //MMWAVEHEADER_FUNC               WriteWaveHeader;

    //MMWAVEHEADER_FUNC               SubmitWaveHeaderToDevice;
    //MMBUFFER_FUNC                   CompleteBuffer;
} MMFUNCTION_TABLE, *PMMFUNCTION_TABLE;



typedef MMRESULT (*SOUND_THREAD_REQUEST_HANDLER)(
    IN  struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance,
    IN  PVOID Parameter);

typedef struct _SOUND_THREAD
{
    HANDLE Handle;
    BOOL Running;

    struct
    {
        HANDLE Ready;
        HANDLE Request;
        HANDLE Done;
    } Events;

    struct
    {
        SOUND_THREAD_REQUEST_HANDLER Handler;
        struct _SOUND_DEVICE_INSTANCE* SoundDeviceInstance;
        PVOID Parameter;
        MMRESULT Result;
    } Request;
} SOUND_THREAD, *PSOUND_THREAD;

typedef struct _SOUND_DEVICE
{
    struct _SOUND_DEVICE* Next;
    struct _SOUND_DEVICE_INSTANCE* HeadInstance;
    struct _SOUND_DEVICE_INSTANCE* TailInstance;
    MMDEVICE_TYPE Type;
    PVOID Identifier;       /* Path for NT4 drivers */
    /*PWSTR Path;*/
    MMFUNCTION_TABLE FunctionTable;
} SOUND_DEVICE, *PSOUND_DEVICE;

typedef struct _SOUND_DEVICE_INSTANCE
{
    struct _SOUND_DEVICE_INSTANCE* Next;
    struct _SOUND_DEVICE* Device;
    PVOID Handle;
    struct _SOUND_THREAD* Thread;

    /* Stuff generously donated to us from WinMM */
    struct
    {
        HDRVR Handle;
        DWORD Flags;
        DWORD_PTR ClientCallback;
        DWORD_PTR ClientCallbackInstanceData;
    } WinMM;

    /* DO NOT TOUCH THESE OUTSIDE OF THE SOUND THREAD */

    union
    {
        PWAVEHDR HeadWaveHeader;
    };

    union
    {
        PWAVEHDR TailWaveHeader;
    };

    PWAVEHDR WaveLoopStart;
    //PWAVEHDR CurrentWaveHeader;
    DWORD OutstandingBuffers;
    DWORD LoopsRemaining;
    DWORD FrameSize;
    DWORD BufferCount;
    WAVEFORMATEX WaveFormatEx;
    HANDLE hNotifyEvent;
    HANDLE hStopEvent;
} SOUND_DEVICE_INSTANCE, *PSOUND_DEVICE_INSTANCE;

/* This lives in WAVEHDR.reserved */
typedef struct _WAVEHDR_EXTENSION
{
    DWORD BytesCommitted;
    DWORD BytesCompleted;
} WAVEHDR_EXTENSION, *PWAVEHDR_EXTENSION;


/*
    reentrancy.c
*/

MMRESULT
InitEntrypointMutexes();

VOID
CleanupEntrypointMutexes();

VOID
AcquireEntrypointMutex(
    IN  MMDEVICE_TYPE DeviceType);

VOID
ReleaseEntrypointMutex(
    IN  MMDEVICE_TYPE DeviceType);


/*
    mme.c
*/

VOID
NotifyMmeClient(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  UINT Message,
    IN  DWORD_PTR Parameter);

MMRESULT
MmeGetSoundDeviceCapabilities(
    IN  MMDEVICE_TYPE DeviceType,
    IN  DWORD DeviceId,
    IN  DWORD_PTR Capabilities,
    IN  DWORD CapabilitiesSize);

MMRESULT
MmeOpenWaveDevice(
    IN  MMDEVICE_TYPE DeviceType,
    IN  UINT DeviceId,
    IN  LPWAVEOPENDESC OpenParameters,
    IN  DWORD Flags,
    OUT SIZE_T* PrivateHandle);

MMRESULT
MmeCloseDevice(
    IN  DWORD_PTR PrivateHandle);

MMRESULT
MmeGetPosition(
    IN  MMDEVICE_TYPE DeviceType,
    IN  DWORD DeviceId,
    IN  DWORD_PTR PrivateHandle,
    IN  MMTIME* Time,
    IN  DWORD Size);

MMRESULT
MmeGetDeviceInterfaceString(
    IN  MMDEVICE_TYPE DeviceType,
    IN  DWORD DeviceId,
    IN  LPWSTR Interface,
    IN  DWORD  InterfaceLength,
    OUT  DWORD * InterfaceSize);


MMRESULT
MmeSetState(
    IN  DWORD_PTR PrivateHandle,
    IN  BOOL bStart);


#define MmePrepareWaveHeader(private_handle, header) \
    PrepareWaveHeader((PSOUND_DEVICE_INSTANCE)private_handle, (PWAVEHDR)header)

#define MmeUnprepareWaveHeader(private_handle, header) \
    UnprepareWaveHeader((PSOUND_DEVICE_INSTANCE)private_handle, (PWAVEHDR)header)

#define MmeWriteWaveHeader(private_handle, header) \
    WriteWaveHeader((PSOUND_DEVICE_INSTANCE)private_handle, (PWAVEHDR)header)

MMRESULT
MmeResetWavePlayback(
    IN  SIZE_T PrivateHandle);


/*
    capabilities.c
*/

MMRESULT
GetSoundDeviceCapabilities(
    IN  PSOUND_DEVICE SoundDevice,
    IN  DWORD DeviceId,
    OUT PVOID Capabilities,
    IN  DWORD CapabilitiesSize);


/*
    devicelist.c
*/

ULONG
GetSoundDeviceCount(
    IN  MMDEVICE_TYPE DeviceType);

BOOLEAN
IsValidSoundDevice(
    IN  PSOUND_DEVICE SoundDevice);

MMRESULT
ListSoundDevice(
    IN  MMDEVICE_TYPE DeviceType,
    IN  PVOID Identifier OPTIONAL,
    OUT PSOUND_DEVICE* SoundDevice OPTIONAL);

MMRESULT
UnlistSoundDevice(
    IN  MMDEVICE_TYPE DeviceType,
    IN  PSOUND_DEVICE SoundDevice);

MMRESULT
UnlistSoundDevices(
    IN  MMDEVICE_TYPE DeviceType);

VOID
UnlistAllSoundDevices();

MMRESULT
GetSoundDevice(
    IN  MMDEVICE_TYPE DeviceType,
    IN  DWORD DeviceIndex,
    OUT PSOUND_DEVICE* Device);

MMRESULT
GetSoundDeviceIdentifier(
    IN  PSOUND_DEVICE SoundDevice,
    OUT PVOID* Identifier);

MMRESULT
GetSoundDeviceType(
    IN  PSOUND_DEVICE SoundDevice,
    OUT PMMDEVICE_TYPE DeviceType);


/*
    functiontable.c
*/

MMRESULT
SetSoundDeviceFunctionTable(
    IN  PSOUND_DEVICE SoundDevice,
    IN  PMMFUNCTION_TABLE FunctionTable);

MMRESULT
GetSoundDeviceFunctionTable(
    IN  PSOUND_DEVICE SoundDevice,
    OUT PMMFUNCTION_TABLE* FunctionTable);


/*
    deviceinstance.c
*/

BOOLEAN
IsValidSoundDeviceInstance(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance);

MMRESULT
CreateSoundDeviceInstance(
    IN  PSOUND_DEVICE SoundDevice,
    OUT PSOUND_DEVICE_INSTANCE* SoundDeviceInstance);

MMRESULT
DestroySoundDeviceInstance(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance);

MMRESULT
DestroyAllSoundDeviceInstances(
    IN  PSOUND_DEVICE SoundDevice);

MMRESULT
GetSoundDeviceFromInstance(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    OUT PSOUND_DEVICE* SoundDevice);

MMRESULT
GetSoundDeviceInstanceHandle(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    OUT PVOID* Handle);

MMRESULT
SetSoundDeviceInstanceMmeData(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  HDRVR MmeHandle,
    IN  DWORD_PTR ClientCallback,
    IN  DWORD_PTR ClientCallbackData,
    IN  DWORD Flags);


/*
    thread.c
*/

MMRESULT
CreateSoundThread(
    OUT PSOUND_THREAD* Thread);

MMRESULT
DestroySoundThread(
    IN  PSOUND_THREAD Thread);

MMRESULT
CallSoundThread(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  SOUND_THREAD_REQUEST_HANDLER RequestHandler,
    IN  PVOID Parameter OPTIONAL);


/*
    utility.c
*/

PVOID
AllocateMemory(
    IN  UINT Size);

VOID
FreeMemory(
    IN  PVOID Pointer);

UINT
GetMemoryAllocationCount();

UINT
GetDigitCount(
    IN  UINT Number);

MMRESULT
Win32ErrorToMmResult(
    IN  UINT ErrorCode);

MMRESULT
TranslateInternalMmResult(
    IN  MMRESULT Result);


/*
    wave/format.c
*/

MMRESULT
QueryWaveDeviceFormatSupport(
    IN  PSOUND_DEVICE SoundDevice,
    IN  LPWAVEFORMATEX Format,
    IN  DWORD FormatSize);

MMRESULT
SetWaveDeviceFormat(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  DWORD DeviceId,
    IN  LPWAVEFORMATEX Format,
    IN  DWORD FormatSize);


/*
    wave/header.c
*/

MMRESULT
EnqueueWaveHeader(
    PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PVOID Parameter);

VOID
CompleteWaveHeader(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PWAVEHDR Header);

MMRESULT
PrepareWaveHeader(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PWAVEHDR Header);

MMRESULT
UnprepareWaveHeader(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PWAVEHDR Header);

MMRESULT
WriteWaveHeader(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PWAVEHDR Header);


/*
    wave/streaming.c
*/

VOID
DoWaveStreaming(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance);

VOID CALLBACK
CompleteIO(
    IN  DWORD dwErrorCode,
    IN  DWORD dwNumberOfBytesTransferred,
    IN  LPOVERLAPPED lpOverlapped);

MMRESULT
CommitWaveHeaderToKernelDevice(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PWAVEHDR Header,
    IN  WAVE_COMMIT_FUNC CommitFunction);

MMRESULT
WriteFileEx_Committer(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    IN  PVOID OffsetPtr,
    IN  DWORD Length,
    IN  PSOUND_OVERLAPPED Overlap,
    IN  LPOVERLAPPED_COMPLETION_ROUTINE CompletionRoutine);

MMRESULT
StopStreaming(
    IN  PSOUND_DEVICE_INSTANCE SoundDeviceInstance);


/*
    kernel.c
*/

MMRESULT
OpenKernelSoundDeviceByName(
    IN  PWSTR DevicePath,
    IN  BOOLEAN ReadOnly,
    OUT PHANDLE Handle);

MMRESULT
OpenKernelSoundDevice(
    IN  PSOUND_DEVICE SoundDevice,
    IN  BOOLEAN ReadOnly,
    OUT PHANDLE Handle);

MMRESULT
CloseKernelSoundDevice(
    IN  HANDLE Handle);

MMRESULT
SyncOverlappedDeviceIoControl(
    IN  HANDLE SoundDeviceInstance,
    IN  DWORD IoControlCode,
    IN  LPVOID InBuffer,
    IN  DWORD InBufferSize,
    OUT LPVOID OutBuffer,
    IN  DWORD OutBufferSize,
    OUT LPDWORD BytesTransferred OPTIONAL);


#endif