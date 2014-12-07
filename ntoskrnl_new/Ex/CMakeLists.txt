
add_library(ntos_ex
    Atom.cpp
    BootConfig.cpp
    Callback.cpp
    Exception.cpp
    FastMutex.cpp
    Interlocked.cpp
    KeyedEvent.cpp
    License.cpp
    LookasideList.cpp
    Pool.cpp
    Processor.cpp
    PushLock.cpp
    Resource.cpp
    RundownProtection.cpp
    RundownCacheAware.cpp
    SpinLock.cpp
    SystemTime.cpp
    Timer.cpp
    WnfState.cpp
    Zone.cpp
    Stubs.c
)

add_dependencies(ntos_ex psdk bugcodes asm)
