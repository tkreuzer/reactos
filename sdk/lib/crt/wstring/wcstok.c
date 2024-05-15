/* taken from wine wcs.c */
#include <precomp.h>

static wchar_t * wcstok_internal( wchar_t *str, const wchar_t *delim,
                                 wchar_t **next_token )
{
    wchar_t *ret;

    if (!str) str = *next_token;

    while (*str && strchrW( delim, *str )) str++;
    if (!*str) return NULL;
    ret = str++;
    while (*str && !strchrW( delim, *str )) str++;
    if (*str) *str++ = 0;
    *next_token = str;
    return ret;
}

/*********************************************************************
 *		wcstok_s  (MSVCRT.@)
 */
wchar_t * CDECL wcstok_s( wchar_t *str, const wchar_t *delim,
                                 wchar_t **next_token )
{
    if (!MSVCRT_CHECK_PMT(delim != NULL) || !MSVCRT_CHECK_PMT(next_token != NULL) ||
        !MSVCRT_CHECK_PMT(str != NULL || *next_token != NULL))
    {
        _set_errno(EINVAL);
        return NULL;
    }

    return wcstok_internal( str, delim, next_token );
}

#if 0
/*********************************************************************
 *		wcstok  (UCRTBASE.@) - Conforming version
 */
wchar_t * CDECL wcstok( wchar_t *str, const wchar_t *delim,
                                 wchar_t **next_token )
{
    if (next_token == NULL)
    {
        next_token = &msvcrt_get_thread_data()->wcstok_next;
    }

    return wcstok_internal(str, delim, next_token);
}
#endif

/*********************************************************************
 *		wcstok  (MSVCRT.@) - Non-conforming version
 */
wchar_t * CDECL MSVCRT_wcstok( wchar_t *str, const wchar_t *delim )
{
    return wcstok_internal(str, delim, &msvcrt_get_thread_data()->wcstok_next);
}
