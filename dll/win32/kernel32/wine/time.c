/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS system libraries
 * FILE:            dll/win32/kernel32/wine/timezone.c
 * PURPOSE:         Time conversion functions
 * PROGRAMMER:      Ariadne
 *                  DOSDATE and DOSTIME structures from Onno Hovers
 * UPDATE HISTORY:
 *                  Created 19/01/99
 */

/* INCLUDES ******************************************************************/

#include <k32.h>

#define NDEBUG
#include <debug.h>
DEBUG_CHANNEL(time);

BOOL NLS_IsUnicodeOnlyLcid(LCID lcid);

/* TYPES *********************************************************************/

#define TICKSPERMIN 600000000

#define CALINFO_MAX_YEAR 2029

#define LL2FILETIME( ll, pft )\
    (pft)->dwLowDateTime = (UINT)(ll); \
    (pft)->dwHighDateTime = (UINT)((ll) >> 32);
#define FILETIME2LL( pft, ll) \
    ll = (((LONGLONG)((pft)->dwHighDateTime))<<32) + (pft)-> dwLowDateTime ;

static const int MonthLengths[2][12] =
{
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/* STATIC FUNCTIONS **********************************************************/

static inline int IsLeapYear(int Year)
{
    return Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0) ? 1 : 0;
}

/***********************************************************************
 *  TIME_DayLightCompareDate
 *
 * Compares two dates without looking at the year.
 *
 * PARAMS
 *   date        [in] The local time to compare.
 *   compareDate [in] The daylight savings begin or end date.
 *
 * RETURNS
 *
 *  -1 if date < compareDate
 *   0 if date == compareDate
 *   1 if date > compareDate
 *  -2 if an error occurs
 */
static int TIME_DayLightCompareDate( const SYSTEMTIME *date,
    const SYSTEMTIME *compareDate )
{
    int limit_day, dayinsecs;

    if (date->wMonth < compareDate->wMonth)
        return -1; /* We are in a month before the date limit. */

    if (date->wMonth > compareDate->wMonth)
        return 1; /* We are in a month after the date limit. */

    /* if year is 0 then date is in day-of-week format, otherwise
     * it's absolute date.
     */
    if (compareDate->wYear == 0)
    {
        WORD First;
        /* compareDate->wDay is interpreted as number of the week in the month
         * 5 means: the last week in the month */
        int weekofmonth = compareDate->wDay;
          /* calculate the day of the first DayOfWeek in the month */
        First = ( 6 + compareDate->wDayOfWeek - date->wDayOfWeek + date->wDay 
               ) % 7 + 1;
        limit_day = First + 7 * (weekofmonth - 1);
        /* check needed for the 5th weekday of the month */
        if(limit_day > MonthLengths[date->wMonth==2 && IsLeapYear(date->wYear)]
                [date->wMonth - 1])
            limit_day -= 7;
    }
    else
    {
       limit_day = compareDate->wDay;
    }

    /* convert to seconds */
    limit_day = ((limit_day * 24  + compareDate->wHour) * 60 +
            compareDate->wMinute ) * 60;
    dayinsecs = ((date->wDay * 24  + date->wHour) * 60 +
            date->wMinute ) * 60 + date->wSecond;
    /* and compare */
    return dayinsecs < limit_day ? -1 :
           dayinsecs > limit_day ? 1 :
           0;   /* date is equal to the date limit. */
}

/***********************************************************************
 *  TIME_CompTimeZoneID
 *
 *  Computes the local time bias for a given time and time zone.
 *
 *  PARAMS
 *      pTZinfo     [in] The time zone data.
 *      lpFileTime  [in] The system or local time.
 *      islocal     [in] it is local time.
 *
 *  RETURNS
 *      TIME_ZONE_ID_INVALID    An error occurred
 *      TIME_ZONE_ID_UNKNOWN    There are no transition time known
 *      TIME_ZONE_ID_STANDARD   Current time is standard time
 *      TIME_ZONE_ID_DAYLIGHT   Current time is daylight savings time
 */
static
DWORD
TIME_CompTimeZoneID( const TIME_ZONE_INFORMATION *pTZinfo, FILETIME *lpFileTime, BOOL islocal )
{
    int ret, year;
    BOOL beforeStandardDate, afterDaylightDate;
    DWORD retval = TIME_ZONE_ID_INVALID;
    LONGLONG llTime = 0; /* initialized to prevent gcc complaining */
    SYSTEMTIME SysTime;
    FILETIME ftTemp;

    if (pTZinfo->DaylightDate.wMonth != 0)
    {
        /* if year is 0 then date is in day-of-week format, otherwise
         * it's absolute date.
         */
        if (pTZinfo->StandardDate.wMonth == 0 ||
            (pTZinfo->StandardDate.wYear == 0 &&
            (pTZinfo->StandardDate.wDay<1 ||
            pTZinfo->StandardDate.wDay>5 ||
            pTZinfo->DaylightDate.wDay<1 ||
            pTZinfo->DaylightDate.wDay>5)))
        {
            SetLastError(ERROR_INVALID_PARAMETER);
            return TIME_ZONE_ID_INVALID;
        }

        if (!islocal) {
            FILETIME2LL( lpFileTime, llTime );
            llTime -= pTZinfo->Bias * (LONGLONG)TICKSPERMIN;
            LL2FILETIME( llTime, &ftTemp)
            lpFileTime = &ftTemp;
        }

        FileTimeToSystemTime(lpFileTime, &SysTime);
        year = SysTime.wYear;

        if (!islocal) {
            llTime -= pTZinfo->DaylightBias * (LONGLONG)TICKSPERMIN;
            LL2FILETIME( llTime, &ftTemp)
            FileTimeToSystemTime(lpFileTime, &SysTime);
        }
        
        /* check for daylight savings */
        if(year == SysTime.wYear) {
            ret = TIME_DayLightCompareDate( &SysTime, &pTZinfo->StandardDate);
            if (ret == -2)
                return TIME_ZONE_ID_INVALID;

            beforeStandardDate = ret < 0;
        } else
            beforeStandardDate = SysTime.wYear < year;

        if (!islocal) {
            llTime -= ( pTZinfo->StandardBias - pTZinfo->DaylightBias )
                * (LONGLONG)TICKSPERMIN;
            LL2FILETIME( llTime, &ftTemp)
            FileTimeToSystemTime(lpFileTime, &SysTime);
        }

        if(year == SysTime.wYear) {
            ret = TIME_DayLightCompareDate( &SysTime, &pTZinfo->DaylightDate);
            if (ret == -2)
                return TIME_ZONE_ID_INVALID;

            afterDaylightDate = ret >= 0;
        } else
            afterDaylightDate = SysTime.wYear > year;

        retval = TIME_ZONE_ID_STANDARD;
        if( pTZinfo->DaylightDate.wMonth <  pTZinfo->StandardDate.wMonth ) {
            /* Northern hemisphere */
            if( beforeStandardDate && afterDaylightDate )
                retval = TIME_ZONE_ID_DAYLIGHT;
        } else    /* Down south */
            if( beforeStandardDate || afterDaylightDate )
            retval = TIME_ZONE_ID_DAYLIGHT;
    } else 
        /* No transition date */
        retval = TIME_ZONE_ID_UNKNOWN;
        
    return retval;
}

/***********************************************************************
 *  TIME_TimeZoneID
 *
 *  Calculates whether daylight savings is on now.
 *
 *  PARAMS
 *      pTzi [in] Timezone info.
 *
 *  RETURNS
 *      TIME_ZONE_ID_INVALID    An error occurred
 *      TIME_ZONE_ID_UNKNOWN    There are no transition time known
 *      TIME_ZONE_ID_STANDARD   Current time is standard time
 *      TIME_ZONE_ID_DAYLIGHT   Current time is daylight savings time
 */
static DWORD TIME_ZoneID( const TIME_ZONE_INFORMATION *pTzi )
{
    FILETIME ftTime;
    GetSystemTimeAsFileTime( &ftTime);
    return TIME_CompTimeZoneID( pTzi, &ftTime, FALSE);
}

/***********************************************************************
 *  TIME_GetTimezoneBias
 *
 *  Calculates the local time bias for a given time zone.
 *
 * PARAMS
 *  pTZinfo    [in]  The time zone data.
 *  lpFileTime [in]  The system or local time.
 *  islocal    [in]  It is local time.
 *  pBias      [out] The calculated bias in minutes.
 *
 * RETURNS
 *  TRUE when the time zone bias was calculated.
 */
static BOOL TIME_GetTimezoneBias( const TIME_ZONE_INFORMATION *pTZinfo,
    FILETIME *lpFileTime, BOOL islocal, LONG *pBias )
{
    LONG bias = pTZinfo->Bias;
    DWORD tzid = TIME_CompTimeZoneID( pTZinfo, lpFileTime, islocal);

    if( tzid == TIME_ZONE_ID_INVALID)
        return FALSE;
    if (tzid == TIME_ZONE_ID_DAYLIGHT)
        bias += pTZinfo->DaylightBias;
    else if (tzid == TIME_ZONE_ID_STANDARD)
        bias += pTZinfo->StandardBias;
    *pBias = bias;
    return TRUE;
}


/* FUNCTIONS ****************************************************************/

/***********************************************************************
 *              GetTimeZoneInformation  (KERNEL32.@)
 *
 *  Get information about the current local time zone.
 *
 * PARAMS
 *  tzinfo [out] Destination for time zone information.
 *
 * RETURNS
 *  TIME_ZONE_ID_INVALID    An error occurred
 *  TIME_ZONE_ID_UNKNOWN    There are no transition time known
 *  TIME_ZONE_ID_STANDARD   Current time is standard time
 *  TIME_ZONE_ID_DAYLIGHT   Current time is daylight savings time
 */
DWORD WINAPI GetTimeZoneInformation( LPTIME_ZONE_INFORMATION tzinfo )
{
    NTSTATUS status;

    DPRINT("GetTimeZoneInformation()\n");

    status = NtQuerySystemInformation(SystemCurrentTimeZoneInformation,
                                      tzinfo,
                                      sizeof(TIME_ZONE_INFORMATION),
                                      NULL);
    if (!NT_SUCCESS(status))
    {
        BaseSetLastNTError(status);
        return TIME_ZONE_ID_INVALID;
    }

    return TIME_ZoneID( tzinfo );
}


/***********************************************************************
 *              SetTimeZoneInformation  (KERNEL32.@)
 *
 *  Change the settings of the current local time zone.
 *
 * PARAMS
 *  tzinfo [in] The new time zone.
 *
 * RETURNS
 *  Success: TRUE. The time zone was updated with the settings from tzinfo.
 *  Failure: FALSE.
 */
BOOL WINAPI SetTimeZoneInformation( const TIME_ZONE_INFORMATION *tzinfo )
{
    RTL_TIME_ZONE_INFORMATION TimeZoneInformation;
    NTSTATUS Status;

    DPRINT("SetTimeZoneInformation()\n");

    Status = RtlSetTimeZoneInformation((LPTIME_ZONE_INFORMATION)tzinfo);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("RtlSetTimeZoneInformation() failed (Status %lx)\n", Status);
        BaseSetLastNTError(Status);
        return FALSE;
    }

    Status = NtSetSystemInformation(SystemCurrentTimeZoneInformation,
                                    (PVOID)tzinfo,
                                    sizeof(TIME_ZONE_INFORMATION));
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("NtSetSystemInformation() failed (Status %lx)\n", Status);
        BaseSetLastNTError(Status);
        return FALSE;
    }

    return TRUE;
}

/***********************************************************************
 *              SystemTimeToTzSpecificLocalTime  (KERNEL32.@)
 *
 *  Convert a utc system time to a local time in a given time zone.
 *
 * PARAMS
 *  lpTimeZoneInformation [in]  The desired time zone.
 *  lpUniversalTime       [in]  The utc time to base local time on.
 *  lpLocalTime           [out] The local time in the time zone.
 *
 * RETURNS
 *  Success: TRUE. lpLocalTime contains the converted time
 *  Failure: FALSE.
 */
BOOL
WINAPI
SystemTimeToTzSpecificLocalTime(CONST TIME_ZONE_INFORMATION *lpTimeZoneInformation,
                                CONST SYSTEMTIME *lpUniversalTime,
                                LPSYSTEMTIME lpLocalTime)
{
    TIME_ZONE_INFORMATION TzInfo;
    FILETIME FileTime;
    LONGLONG llTime;
    LONG lBias;

    if (lpTimeZoneInformation != NULL)
    {
        TzInfo = *lpTimeZoneInformation;
    }
    else
    {
        if (GetTimeZoneInformation(&TzInfo) == TIME_ZONE_ID_INVALID)
            return FALSE;
    }

    if (!lpUniversalTime || !lpLocalTime)
        return FALSE;

    if (!SystemTimeToFileTime(lpUniversalTime, &FileTime))
        return FALSE;

    FILETIME2LL(&FileTime, llTime)

    if (!TIME_GetTimezoneBias(&TzInfo, &FileTime, FALSE, &lBias))
        return FALSE;

    /* convert minutes to 100-nanoseconds-ticks */
    llTime -= (LONGLONG)lBias * TICKSPERMIN;

    LL2FILETIME( llTime, &FileTime)

    return FileTimeToSystemTime(&FileTime, lpLocalTime);
}


/***********************************************************************
 *              TzSpecificLocalTimeToSystemTime  (KERNEL32.@)
 *
 *  Converts a local time to a time in utc.
 *
 * PARAMS
 *  lpTimeZoneInformation [in]  The desired time zone.
 *  lpLocalTime           [in]  The local time.
 *  lpUniversalTime       [out] The calculated utc time.
 *
 * RETURNS
 *  Success: TRUE. lpUniversalTime contains the converted time.
 *  Failure: FALSE.
 */
BOOL
WINAPI
TzSpecificLocalTimeToSystemTime(LPTIME_ZONE_INFORMATION lpTimeZoneInformation,
                                LPSYSTEMTIME lpLocalTime,
                                LPSYSTEMTIME lpUniversalTime)
{
    FILETIME ft;
    LONG lBias;
    LONGLONG t;
    TIME_ZONE_INFORMATION tzinfo;

    if (lpTimeZoneInformation != NULL)
    {
        tzinfo = *lpTimeZoneInformation;
    }
    else
    {
        if (GetTimeZoneInformation(&tzinfo) == TIME_ZONE_ID_INVALID)
            return FALSE;
    }

    if (!SystemTimeToFileTime(lpLocalTime, &ft))
        return FALSE;
    FILETIME2LL( &ft, t)
    if (!TIME_GetTimezoneBias(&tzinfo, &ft, TRUE, &lBias))
        return FALSE;
    /* convert minutes to 100-nanoseconds-ticks */
    t += (LONGLONG)lBias * TICKSPERMIN;
    LL2FILETIME( t, &ft)
    return FileTimeToSystemTime(&ft, lpUniversalTime);
}

/*********************************************************************
 *	GetCalendarInfoA				(KERNEL32.@)
 *
 */
int WINAPI GetCalendarInfoA(LCID lcid, CALID Calendar, CALTYPE CalType,
			    LPSTR lpCalData, int cchData, LPDWORD lpValue)
{
    int ret, cchDataW = cchData;
    LPWSTR lpCalDataW = NULL;
#ifdef __REACTOS__
    DWORD cp = CP_ACP;
    if (!(CalType & CAL_USE_CP_ACP))
    {
        DWORD dwFlags = ((CalType & CAL_NOUSEROVERRIDE) ? LOCALE_NOUSEROVERRIDE : 0);
        const NLS_FORMAT_NODE *node = NLS_GetFormats(lcid, dwFlags);
        if (!node)
        {
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }
        cp = node->dwCodePage;
    }
    if ((CalType & 0xFFFF) == CAL_SABBREVERASTRING)
    {
        /* NOTE: CAL_SABBREVERASTRING is not supported in GetCalendarInfoA */
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }
#endif

    if (NLS_IsUnicodeOnlyLcid(lcid))
    {
      SetLastError(ERROR_INVALID_PARAMETER);
      return 0;
    }

    if (!cchData && !(CalType & CAL_RETURN_NUMBER))
        cchDataW = GetCalendarInfoW(lcid, Calendar, CalType, NULL, 0, NULL);
    if (!(lpCalDataW = HeapAlloc(GetProcessHeap(), 0, cchDataW*sizeof(WCHAR))))
        return 0;

    ret = GetCalendarInfoW(lcid, Calendar, CalType, lpCalDataW, cchDataW, lpValue);
    if(ret && lpCalDataW && lpCalData)
#ifdef __REACTOS__
        ret = WideCharToMultiByte(cp, 0, lpCalDataW, -1, lpCalData, cchData, NULL, NULL);
#else
        ret = WideCharToMultiByte(CP_ACP, 0, lpCalDataW, -1, lpCalData, cchData, NULL, NULL);
#endif
    else if (CalType & CAL_RETURN_NUMBER)
        ret *= sizeof(WCHAR);
    HeapFree(GetProcessHeap(), 0, lpCalDataW);

    return ret;
}

/*********************************************************************
 *	GetCalendarInfoW				(KERNEL32.@)
 *
 */
int WINAPI GetCalendarInfoW(LCID Locale, CALID Calendar, CALTYPE CalType,
			    LPWSTR lpCalData, int cchData, LPDWORD lpValue)
{
    static const LCTYPE caltype_lctype_map[] = {
        0, /* not used */
        0, /* CAL_ICALINTVALUE */
        0, /* CAL_SCALNAME */
        0, /* CAL_IYEAROFFSETRANGE */
        0, /* CAL_SERASTRING */
        LOCALE_SSHORTDATE,
        LOCALE_SLONGDATE,
        LOCALE_SDAYNAME1,
        LOCALE_SDAYNAME2,
        LOCALE_SDAYNAME3,
        LOCALE_SDAYNAME4,
        LOCALE_SDAYNAME5,
        LOCALE_SDAYNAME6,
        LOCALE_SDAYNAME7,
        LOCALE_SABBREVDAYNAME1,
        LOCALE_SABBREVDAYNAME2,
        LOCALE_SABBREVDAYNAME3,
        LOCALE_SABBREVDAYNAME4,
        LOCALE_SABBREVDAYNAME5,
        LOCALE_SABBREVDAYNAME6,
        LOCALE_SABBREVDAYNAME7,
        LOCALE_SMONTHNAME1,
        LOCALE_SMONTHNAME2,
        LOCALE_SMONTHNAME3,
        LOCALE_SMONTHNAME4,
        LOCALE_SMONTHNAME5,
        LOCALE_SMONTHNAME6,
        LOCALE_SMONTHNAME7,
        LOCALE_SMONTHNAME8,
        LOCALE_SMONTHNAME9,
        LOCALE_SMONTHNAME10,
        LOCALE_SMONTHNAME11,
        LOCALE_SMONTHNAME12,
        LOCALE_SMONTHNAME13,
        LOCALE_SABBREVMONTHNAME1,
        LOCALE_SABBREVMONTHNAME2,
        LOCALE_SABBREVMONTHNAME3,
        LOCALE_SABBREVMONTHNAME4,
        LOCALE_SABBREVMONTHNAME5,
        LOCALE_SABBREVMONTHNAME6,
        LOCALE_SABBREVMONTHNAME7,
        LOCALE_SABBREVMONTHNAME8,
        LOCALE_SABBREVMONTHNAME9,
        LOCALE_SABBREVMONTHNAME10,
        LOCALE_SABBREVMONTHNAME11,
        LOCALE_SABBREVMONTHNAME12,
        LOCALE_SABBREVMONTHNAME13,
        LOCALE_SYEARMONTH,
        0, /* CAL_ITWODIGITYEARMAX */
#if (WINVER >= 0x0600) /* ReactOS */
        LOCALE_SSHORTESTDAYNAME1,
        LOCALE_SSHORTESTDAYNAME2,
        LOCALE_SSHORTESTDAYNAME3,
        LOCALE_SSHORTESTDAYNAME4,
        LOCALE_SSHORTESTDAYNAME5,
        LOCALE_SSHORTESTDAYNAME6,
        LOCALE_SSHORTESTDAYNAME7,
#endif
        LOCALE_SMONTHDAY,
        0, /* CAL_SABBREVERASTRING */
    };
    DWORD localeflags = 0;
    CALTYPE calinfo;

    if (CalType & CAL_NOUSEROVERRIDE)
	FIXME("flag CAL_NOUSEROVERRIDE used, not fully implemented\n");
    if (CalType & CAL_USE_CP_ACP)
	FIXME("flag CAL_USE_CP_ACP used, not fully implemented\n");

    if (CalType & CAL_RETURN_NUMBER) {
        if (!lpValue)
        {
            SetLastError( ERROR_INVALID_PARAMETER );
            return 0;
        }
	if (lpCalData != NULL)
	    WARN("lpCalData not NULL (%p) when it should!\n", lpCalData);
	if (cchData != 0)
	    WARN("cchData not 0 (%d) when it should!\n", cchData);
    } else {
	if (lpValue != NULL)
	    WARN("lpValue not NULL (%p) when it should!\n", lpValue);
    }

    /* FIXME: No verification is made yet wrt Locale
     * for the CALTYPES not requiring GetLocaleInfoA */

    calinfo = CalType & 0xffff;

#ifdef __REACTOS__
    if (CalType & LOCALE_RETURN_GENITIVE_NAMES)
#else
    if (CalType & CAL_RETURN_GENITIVE_NAMES)
#endif
        localeflags |= LOCALE_RETURN_GENITIVE_NAMES;

    switch (calinfo) {
	case CAL_ICALINTVALUE:
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(Locale))
        {
            if (CalType & CAL_RETURN_NUMBER)
            {
                *lpValue = CAL_JAPAN;
                return sizeof(DWORD) / sizeof(WCHAR);
            }
            else
            {
                static const WCHAR fmtW[] = {'%','u',0};
                WCHAR buffer[10];
                int ret = snprintfW( buffer, 10, fmtW, CAL_JAPAN ) + 1;
                if (!lpCalData) return ret;
                if (ret <= cchData)
                {
                    strcpyW( lpCalData, buffer );
                    return ret;
                }
                SetLastError( ERROR_INSUFFICIENT_BUFFER );
                return 0;
            }
        }
#endif
            if (CalType & CAL_RETURN_NUMBER)
                return GetLocaleInfoW(Locale, LOCALE_RETURN_NUMBER | LOCALE_ICALENDARTYPE,
                        (LPWSTR)lpValue, 2);
            return GetLocaleInfoW(Locale, LOCALE_ICALENDARTYPE, lpCalData, cchData);
	case CAL_SCALNAME:
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(Locale) && Calendar == CAL_JAPAN)
        {
            // Wareki
            lpCalData[0] = 0x548C;
            lpCalData[1] = 0x66A6;
            lpCalData[2] = 0;
            return 3;
        }
#endif
            FIXME("Unimplemented caltype %d\n", calinfo);
            if (lpCalData) *lpCalData = 0;
	    return 1;
	case CAL_IYEAROFFSETRANGE:
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(Locale) && Calendar == CAL_JAPAN)
        {
            PCJAPANESE_ERA pEra = JapaneseEra_Find(NULL);
            if (pEra)
            {
                if (CalType & CAL_RETURN_NUMBER)
                {
                    *lpValue = pEra->wYear;
                    return sizeof(DWORD) / sizeof(WCHAR);
                }
                else
                {
                    static const WCHAR fmtW[] = {'%','u',0};
                    WCHAR buffer[10];
                    int ret = snprintfW( buffer, 10, fmtW, pEra->wYear ) + 1;
                    if (!lpCalData) return ret;
                    if (ret <= cchData)
                    {
                        strcpyW( lpCalData, buffer );
                        return ret;
                    }
                    SetLastError( ERROR_INSUFFICIENT_BUFFER );
                    return 0;
                }
            }
            else
            {
                SetLastError(ERROR_INVALID_PARAMETER);
                return 0;
            }
        }
#endif
            FIXME("Unimplemented caltype %d\n", calinfo);
	    return 0;
	case CAL_SERASTRING:
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(Locale) && Calendar == CAL_JAPAN)
        {
            PCJAPANESE_ERA pEra = JapaneseEra_Find(NULL);
            if (pEra)
            {
                RtlStringCchCopyW(lpCalData, cchData, pEra->szEraName);
                return strlenW(lpCalData) + 1;
            }
            else
            {
                SetLastError(ERROR_INVALID_PARAMETER);
                return 0;
            }
        }
#endif
            FIXME("Unimplemented caltype %d\n", calinfo);
	    return 0;
	case CAL_SSHORTDATE:
	case CAL_SLONGDATE:
	case CAL_SDAYNAME1:
	case CAL_SDAYNAME2:
	case CAL_SDAYNAME3:
	case CAL_SDAYNAME4:
	case CAL_SDAYNAME5:
	case CAL_SDAYNAME6:
	case CAL_SDAYNAME7:
	case CAL_SABBREVDAYNAME1:
	case CAL_SABBREVDAYNAME2:
	case CAL_SABBREVDAYNAME3:
	case CAL_SABBREVDAYNAME4:
	case CAL_SABBREVDAYNAME5:
	case CAL_SABBREVDAYNAME6:
	case CAL_SABBREVDAYNAME7:
	case CAL_SMONTHNAME1:
	case CAL_SMONTHNAME2:
	case CAL_SMONTHNAME3:
	case CAL_SMONTHNAME4:
	case CAL_SMONTHNAME5:
	case CAL_SMONTHNAME6:
	case CAL_SMONTHNAME7:
	case CAL_SMONTHNAME8:
	case CAL_SMONTHNAME9:
	case CAL_SMONTHNAME10:
	case CAL_SMONTHNAME11:
	case CAL_SMONTHNAME12:
	case CAL_SMONTHNAME13:
	case CAL_SABBREVMONTHNAME1:
	case CAL_SABBREVMONTHNAME2:
	case CAL_SABBREVMONTHNAME3:
	case CAL_SABBREVMONTHNAME4:
	case CAL_SABBREVMONTHNAME5:
	case CAL_SABBREVMONTHNAME6:
	case CAL_SABBREVMONTHNAME7:
	case CAL_SABBREVMONTHNAME8:
	case CAL_SABBREVMONTHNAME9:
	case CAL_SABBREVMONTHNAME10:
	case CAL_SABBREVMONTHNAME11:
	case CAL_SABBREVMONTHNAME12:
	case CAL_SABBREVMONTHNAME13:
	case CAL_SYEARMONTH:
            return GetLocaleInfoW(Locale, caltype_lctype_map[calinfo] | localeflags, lpCalData, cchData);
	case CAL_ITWODIGITYEARMAX:
#ifdef __REACTOS__
        if (IS_LCID_JAPANESE(Locale) && Calendar == CAL_JAPAN)
        {
            if (CalType & CAL_RETURN_NUMBER)
            {
                *lpValue = JAPANESE_MAX_TWODIGITYEAR;
                return sizeof(DWORD) / sizeof(WCHAR);
            }
            else
            {
                static const WCHAR fmtW[] = {'%','u',0};
                WCHAR buffer[10];
                int ret = snprintfW( buffer, 10, fmtW, JAPANESE_MAX_TWODIGITYEAR ) + 1;
                if (!lpCalData) return ret;
                if (ret <= cchData)
                {
                    strcpyW( lpCalData, buffer );
                    return ret;
                }
                SetLastError( ERROR_INSUFFICIENT_BUFFER );
                return 0;
            }
        }
#endif
            if (CalType & CAL_RETURN_NUMBER)
            {
                *lpValue = CALINFO_MAX_YEAR;
                return sizeof(DWORD) / sizeof(WCHAR);
            }
            else
            {
                static const WCHAR fmtW[] = {'%','u',0};
                WCHAR buffer[10];
                int ret = snprintfW( buffer, 10, fmtW, CALINFO_MAX_YEAR  ) + 1;
                if (!lpCalData) return ret;
                if (ret <= cchData)
                {
                    strcpyW( lpCalData, buffer );
                    return ret;
                }
                SetLastError( ERROR_INSUFFICIENT_BUFFER );
                return 0;
            }
	    break;
#ifdef __REACTOS__
    case CAL_SABBREVERASTRING:
        if (IS_LCID_JAPANESE(Locale) && Calendar == CAL_JAPAN)
        {
            PCJAPANESE_ERA pEra = JapaneseEra_Find(NULL);
            if (pEra)
            {
                RtlStringCchCopyW(lpCalData, cchData, pEra->szEraAbbrev);
                return strlenW(lpCalData) + 1;
            }
        }
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
#endif
	default:
            FIXME("Unknown caltype %d\n", calinfo);
            SetLastError(ERROR_INVALID_FLAGS);
            return 0;
    }
    return 0;
}

#if _WIN32_WINNT >= 0x600
/*********************************************************************
 *	GetCalendarInfoEx				(KERNEL32.@)
 */
int WINAPI GetCalendarInfoEx(LPCWSTR locale, CALID calendar, LPCWSTR lpReserved, CALTYPE caltype,
    LPWSTR data, int len, DWORD *value)
{
    static int once;

    LCID lcid = LocaleNameToLCID(locale, 0);
    if (!once++)
        FIXME("(%s, %d, %p, 0x%08x, %p, %d, %p): semi-stub\n", debugstr_w(locale), calendar, lpReserved, caltype,
        data, len, value);
    return GetCalendarInfoW(lcid, calendar, caltype, data, len, value);
}
#endif

/*********************************************************************
 *	SetCalendarInfoA				(KERNEL32.@)
 *
 */
int WINAPI	SetCalendarInfoA(LCID Locale, CALID Calendar, CALTYPE CalType, LPCSTR lpCalData)
{
    FIXME("(%08x,%08x,%08x,%s): stub\n",
	  Locale, Calendar, CalType, debugstr_a(lpCalData));
    return 0;
}

/*********************************************************************
 *	SetCalendarInfoW				(KERNEL32.@)
 *
 *
 */
int WINAPI	SetCalendarInfoW(LCID Locale, CALID Calendar, CALTYPE CalType, LPCWSTR lpCalData)
{
    FIXME("(%08x,%08x,%08x,%s): stub\n",
	  Locale, Calendar, CalType, debugstr_w(lpCalData));
    return 0;
}

/* EOF */
