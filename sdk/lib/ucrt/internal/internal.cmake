
list(APPEND CRT_INTERNAL_SOURCES
    internal/CreateProcessA.cpp
    internal/GetModuleFileNameA.cpp
    internal/GetStringTypeW.c
    internal/initialization.cpp
    internal/LoadLibraryExA.cpp
    internal/locks.cpp
    internal/MultiByteToWideChar.c
    internal/OutputDebugStringA.cpp
    internal/peb_access.cpp
    internal/per_thread_data.cpp
    internal/report_runtime_error.cpp
    internal/SetCurrentDirectoryA.cpp
    internal/SetEnvironmentVariableA.cpp
    internal/shared_initialization.cpp
    internal/WideCharToMultiByte.c
    internal/winapi_thunks.cpp
    internal/win_policies.cpp
)
