
list(APPEND CRT_STRING_SOURCES
    string/memchr.c
    string/memcpy_s.cpp
    string/memicmp.cpp
    string/memset.c
    string/strcat_s.cpp
    string/strchr.c
    string/strcoll.cpp
    string/strcpy_s.cpp
    string/strdup.cpp
    string/stricmp.cpp
    string/stricoll.cpp
    string/strlwr.cpp
    string/strncat_s.cpp
    string/strncnt.cpp
    string/strncoll.cpp
    string/strncpy_s.cpp
    string/strnicmp.cpp
    string/strnicol.cpp
    string/strnlen.cpp
    string/strnset_s.cpp
    string/strset_s.cpp
    string/strstr.c
    string/strtok.cpp
    string/strtok_s.cpp
    string/strupr.cpp
    string/strxfrm.cpp
    string/wcscat.cpp
    string/wcscat_s.cpp
    string/wcscmp.cpp
    string/wcscoll.cpp
    string/wcscpy.cpp
    string/wcscpy_s.cpp
    string/wcscspn.cpp
    string/wcsdup.cpp
    string/wcsicmp.cpp
    string/wcsicoll.cpp
    string/wcslwr.cpp
    string/wcsncat.cpp
    string/wcsncat_s.cpp
    string/wcsncmp.cpp
    string/wcsncnt.cpp
    string/wcsncoll.cpp
    string/wcsncpy.cpp
    string/wcsncpy_s.cpp
    string/wcsnicmp.cpp
    string/wcsnicol.cpp
    string/wcsnset.cpp
    string/wcsnset_s.cpp
    string/wcspbrk.cpp
    string/wcsrchr.c
    string/wcsrev.cpp
    string/wcsset.cpp
    string/wcsset_s.cpp
    string/wcsspn.cpp
    string/wcsstr.c
    string/wcstok.cpp
    string/wcstok_s.cpp
    string/wcsupr.cpp
    string/wcsxfrm.cpp
    string/wmemcpy_s.cpp
    string/wmemmove_s.cpp
)

if(${UCRT_ARCH} STREQUAL "x86")
    list(APPEND CRT_STRING_ASM_SOURCES
        string/i386/_memicmp.asm
        string/i386/_strnicm.asm
        string/i386/memccpy.asm
        string/i386/strnset.asm
        string/i386/strrev.asm
        string/i386/strset.asm
    )
else()
    list(APPEND CRT_STRING_SOURCES
        string/memccpy.c
        string/strnset.c
        string/strrev.c
        string/strset.c
    )
endif()

if(${UCRT_ARCH} STREQUAL "x86")
    list(APPEND CRT_STRING_ASM_SOURCES
        string/i386/strcat.asm
        string/i386/strcmp.asm
        string/i386/strcspn.asm
        string/i386/strlen.asm
        string/i386/strncat.asm
        string/i386/strncmp.asm
        string/i386/strncpy.asm
        string/i386/strpbrk.asm
        string/i386/strspn.asm
    )
elseif(${UCRT_ARCH} STREQUAL "x64")
    list(APPEND CRT_STRING_SOURCES
        string/amd64/strcspn.c
        string/amd64/strpbrk.c
        string/amd64/strspn.c
    )
    list(APPEND CRT_STRING_ASM_SOURCES
        string/amd64/strcat.asm
        string/amd64/strcmp.asm
        string/amd64/strlen.asm
        string/amd64/strncat.asm
        string/amd64/strncmp.asm
        string/amd64/strncpy.asm
    )
else()
    if(${UCRT_ARCH} STREQUAL "arm64")
        list(APPEND CRT_STRING_ASM_SOURCES
            string/arm64/strlen.asm
            string/arm64/wcslen.asm
    )
    else()
        list(APPEND CRT_STRING_SOURCES
            string/strlen.c
            #string/wcslen.c
        )
    endif()

    list(APPEND CRT_STRING_SOURCES
        string/strcat.c
        string/strcmp.c
        string/strcspn.c
        string/strncat.c
        string/strncmp.c
        string/strncpy.c
        string/strpbrk.c
        string/strspn.c
    )
endif()

#add_asm_files(ucrt_string_asm ${CRT_STRING_ASM_SOURCES})
#list(APPEND CRT_STRING_SOURCES
#    ${ucrt_string_asm}
#)

# HACK, because asm is broken!
list(APPEND CRT_STRING_SOURCES
    string/strcat.c
    string/strcmp.c
    string/strcspn.c
    string/strncat.c
    string/strncmp.c
    string/strncpy.c
    string/strpbrk.c
    string/strspn.c
)

