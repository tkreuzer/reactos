
list(APPEND SOURCE
    asn.c
    bitmap.c
    bsops.c
    cache.c
    channels.c
    iso.c
    licence.c
    mcs.c
    mppc.c
    orders.c
    pstcache.c
    rdp5.c
    rdp.c
    secure.c
    ssl_calls.c
    tcp.c
    uimain.c
    bsops.h
    constants.h
    orders.h
    proto.h
    rdesktop.h
    types.h
    uimain.h
    precomp.h)

add_definitions(-DWITH_SSL -D_UNICODE -DUNICODE)
add_library(rdesktop ${SOURCE})
add_importlibs(rdesktop msvcrt)
