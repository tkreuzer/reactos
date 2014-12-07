
list(APPEND SOURCE
    Access.cpp
    Acl.cpp
    AppContainer.cpp
    AtomTable.cpp
    AvlTable.cpp
    ByteSwap.cpp
    Bitmap.cpp
    Compression.cpp
    Context.cpp
    Crc.cpp
    ErrorMapping.cpp
    GenericTable.cpp
    Guid.cpp
    HashString.cpp
    HashTable.cpp
    Heap.cpp
    Image.cpp
    IntegerConvert.cpp
    Ip2String.cpp
    Luid.cpp
    MemIoResource.cpp
    Memory.cpp
    Misc.cpp
    Nls.cpp
    PrefixTable.cpp
    RangeList.cpp
    Random.cpp
    RbTree.cpp
    Registry.cpp
    Resource.cpp
    RunOnce.cpp
    SecurityDescriptor.cpp
    Sid.cpp
    SList.cpp
    SplayTree.cpp
    String.cpp
    SysInfo.cpp
    Time.cpp
    Token.cpp
    TraceDatabase.cpp
    Unicode.cpp
    UnicodePrefix.cpp
    Unwind.cpp
    Version.cpp
)

if(ARCH STREQUAL "i386")
  list(APPEND SOURCE
      Interlocked.cpp
      LargeInteger.cpp
  )
endif()

if(ARCH STREQUAL "amd64")
  list(APPEND SOURCE
      Bitmap64.cpp
  )
endif()

add_library(ntos_rtl  ${SOURCE})

add_dependencies(ntos_rtl psdk bugcodes asm)
