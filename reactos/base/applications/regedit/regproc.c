/*
 * Registry processing routines. Routines, common for registry
 * processing frontends.
 *
 * Copyright 1999 Sylvain St-Germain
 * Copyright 2002 Andriy Palamarchuk
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <regedit.h>

#define REG_VAL_BUF_SIZE        4096

/* maximal number of characters in hexadecimal data line,
   not including '\' character */
#define REG_FILE_HEX_LINE_LEN   76

/* Globals used by the api setValue */
static LPSTR currentKeyName   = NULL;
static HKEY  currentKeyClass  = 0;
static HKEY  currentKeyHandle = 0;
static BOOL  bTheKeyIsOpen    = FALSE;

static const CHAR *app_name = "UNKNOWN";

static const CHAR *reg_class_names[] = {
                                     "HKEY_LOCAL_MACHINE", "HKEY_USERS", "HKEY_CLASSES_ROOT",
                                     "HKEY_CURRENT_CONFIG", "HKEY_CURRENT_USER", "HKEY_DYN_DATA"
                                 };

#define REG_CLASS_NUMBER (sizeof(reg_class_names) / sizeof(reg_class_names[0]))

static HKEY reg_class_keys[REG_CLASS_NUMBER] = {
            HKEY_LOCAL_MACHINE, HKEY_USERS, HKEY_CLASSES_ROOT,
            HKEY_CURRENT_CONFIG, HKEY_CURRENT_USER, HKEY_DYN_DATA
        };

/* return values */
#define NOT_ENOUGH_MEMORY     1
#define IO_ERROR              2

/* processing macros */

/* common check of memory allocation results */
#define CHECK_ENOUGH_MEMORY(p) \
if (!(p)) \
{ \
    fprintf(stderr,"%s: file %s, line %d: Not enough memory\n", \
            getAppName(), __FILE__, __LINE__); \
    exit(NOT_ENOUGH_MEMORY); \
}

/******************************************************************************
 * This is a replacement for strsep which is not portable (missing on Solaris).
 */
#if 0
/* DISABLED */
char* getToken(char** str, const char* delims)
{
    char* token;

    if (*str==NULL) {
        /* No more tokens */
        return NULL;
    }

    token=*str;
    while (**str!='\0') {
        if (strchr(delims,**str)!=NULL) {
            **str='\0';
            (*str)++;
            return token;
        }
        (*str)++;
    }
    /* There is no other token */
    *str=NULL;
    return token;
}
#endif

/******************************************************************************
 * Copies file name from command line string to the buffer.
 * Rewinds the command line string pointer to the next non-space character
 * after the file name.
 * Buffer contains an empty string if no filename was found;
 *
 * params:
 * command_line - command line current position pointer
 *      where *s[0] is the first symbol of the file name.
 * file_name - buffer to write the file name to.
 */
void get_file_name(CHAR **command_line, CHAR *file_name)
{
    CHAR *s = *command_line;
    int pos = 0;                /* position of pointer "s" in *command_line */
    file_name[0] = 0;

    if (!s[0]) {
        return;
    }

    if (s[0] == '"') {
        s++;
        (*command_line)++;
        while(s[0] != '"') {
            if (!s[0]) {
                fprintf(stderr,"%s: Unexpected end of file name!\n",
                        getAppName());
                exit(1);
            }
            s++;
            pos++;
        }
    } else {
        while(s[0] && !isspace(s[0])) {
            s++;
            pos++;
        }
    }
    memcpy(file_name, *command_line, pos * sizeof((*command_line)[0]));
    /* remove the last backslash */
    if (file_name[pos - 1] == '\\') {
        file_name[pos - 1] = '\0';
    } else {
        file_name[pos] = '\0';
    }

    if (s[0]) {
        s++;
        pos++;
    }
    while(s[0] && isspace(s[0])) {
        s++;
        pos++;
    }
    (*command_line) += pos;
}


/******************************************************************************
 * Converts a hex representation of a DWORD into a DWORD.
 */
static BOOL convertHexToDWord(char* str, DWORD *dw)
{
    char dummy;
    if (strlen(str) > 8 || sscanf(str, "%lx%c", dw, &dummy) != 1) {
        fprintf(stderr,"%s: ERROR, invalid hex value\n", getAppName());
        return FALSE;
    }
    return TRUE;
}

/******************************************************************************
* Converts a hex comma separated values list into a binary string.
  */
static BYTE* convertHexCSVToHex(char *str, DWORD *size)
{
    char *s;
    BYTE *d, *data;

    /* The worst case is 1 digit + 1 comma per byte */
    *size=(strlen(str)+1)/2;
    data=HeapAlloc(GetProcessHeap(), 0, *size);
    CHECK_ENOUGH_MEMORY(data);

    s = str;
    d = data;
    *size=0;
    while (*s != '\0') {
        UINT wc;
        char dummy;

        if (s[1] != ',' && s[1] != '\0' && s[2] != ',' && s[2] != '\0') {
            fprintf(stderr,"%s: ERROR converting CSV hex stream. Invalid sequence at '%s'\n",
                    getAppName(), s);
            HeapFree(GetProcessHeap(), 0, data);
            return NULL;
        }
        if (sscanf(s, "%x%c", &wc, &dummy) < 1 || dummy != ',') {
            fprintf(stderr,"%s: ERROR converting CSV hex stream. Invalid value at '%s'\n",
                    getAppName(), s);
            HeapFree(GetProcessHeap(), 0, data);
            return NULL;
        }
        *d++ =(BYTE)wc;
        (*size)++;
        /* Skip one or two digits and any comma */
        while (*s && *s!=',') s++;
        if (*s) s++;
    }

    return data;
}

/******************************************************************************
 * This function returns the HKEY associated with the data type encoded in the
 * value.  It modifies the input parameter (key value) in order to skip this
 * "now useless" data type information.
 *
 * Note: Updated based on the algorithm used in 'server/registry.c'
 */
DWORD getDataType(LPSTR *lpValue, DWORD* parse_type)
{
    struct data_type { const char *tag; int len; int type; int parse_type; };

    static const struct data_type data_types[] = {                   /* actual type */  /* type to assume for parsing */
                { "\"",        1,   REG_SZ,              REG_SZ },
                { "str:\"",    5,   REG_SZ,              REG_SZ },
                { "str(2):\"", 8,   REG_EXPAND_SZ,       REG_SZ },
                { "hex:",      4,   REG_BINARY,          REG_BINARY },
                { "dword:",    6,   REG_DWORD,           REG_DWORD },
                { "hex(",      4,   -1,                  REG_BINARY },
                { NULL,        0,    0,                  0 }
            };

    const struct data_type *ptr;
    int type;

    for (ptr = data_types; ptr->tag; ptr++) {
        if (memcmp( ptr->tag, *lpValue, ptr->len ))
            continue;

        /* Found! */
        *parse_type = ptr->parse_type;
        type=ptr->type;
        *lpValue+=ptr->len;
        if (type == -1) {
            char* end;
            /* "hex(xx):" is special */
            type = (int)strtoul( *lpValue , &end, 16 );
            if (**lpValue=='\0' || *end!=')' || *(end+1)!=':') {
                type=REG_NONE;
            } else {
                *lpValue=end+2;
            }
        }
        return type;
    }
    *parse_type=REG_NONE;
    return REG_NONE;
}

/******************************************************************************
 * Returns an allocated buffer with a cleaned copy (removed the surrounding
 * dbl quotes) of the passed value.
 */
LPSTR getArg( LPSTR arg)
{
    LPSTR tmp = NULL;
    size_t len;

    if (arg == NULL)
        return NULL;

    /*
     * Get rid of surrounding quotes
     */
    len = strlen(arg);

    if( arg[len-1] == '\"' ) arg[len-1] = '\0';
    if( arg[0]     == '\"' ) arg++;

    tmp = HeapAlloc(GetProcessHeap(), 0, strlen(arg)+1);
    CHECK_ENOUGH_MEMORY(tmp);
    strcpy(tmp, arg);

    return tmp;
}

/******************************************************************************
 * Replaces escape sequences with the characters.
 */
static void REGPROC_unescape_string(LPSTR str)
{
    size_t str_idx = 0;            /* current character under analysis */
    size_t val_idx = 0;            /* the last character of the unescaped string */
    size_t len = strlen(str);
    for (str_idx = 0; str_idx < len; str_idx++, val_idx++) {
        if (str[str_idx] == '\\') {
            str_idx++;
            switch (str[str_idx]) {
            case 'n':
                str[val_idx] = '\n';
                break;
            case '\\':
            case '"':
                str[val_idx] = str[str_idx];
                break;
            default:
                fprintf(stderr,"Warning! Unrecognized escape sequence: \\%c'\n",
                        str[str_idx]);
                str[val_idx] = str[str_idx];
                break;
            }
        } else {
            str[val_idx] = str[str_idx];
        }
    }
    str[val_idx] = '\0';
}

/******************************************************************************
 * Sets the value with name val_name to the data in val_data for the currently
 * opened key.
 *
 * Parameters:
 * val_name - name of the registry value
 * val_data - registry value data
 */
LONG setValue(LPSTR val_name, LPSTR val_data)
{
    LONG res;
    DWORD  dwDataType, dwParseType;
    LPBYTE lpbData;
    DWORD  dwData, dwLen;

    if ( (val_name == NULL) || (val_data == NULL) )
        return ERROR_INVALID_PARAMETER;

    if (strcmp(val_data, "-") == 0)
    {
        res=RegDeleteValueA(currentKeyHandle,val_name);
        return (res == ERROR_FILE_NOT_FOUND ? ERROR_SUCCESS : res);
    }

    /* Get the data type stored into the value field */
    dwDataType = getDataType(&val_data, &dwParseType);

    if (dwParseType == REG_SZ)        /* no conversion for string */
    {
        dwLen = (DWORD) strlen(val_data);
        if (dwLen>0 && val_data[dwLen-1]=='"')
        {
            dwLen--;
            val_data[dwLen]='\0';
        }
        dwLen++;
        REGPROC_unescape_string(val_data);
        lpbData = (LPBYTE)val_data;
    }
    else if (dwParseType == REG_DWORD)  /* Convert the dword types */
    {
        if (!convertHexToDWord(val_data, &dwData))
            return ERROR_INVALID_DATA;
        lpbData = (BYTE*)&dwData;
        dwLen = sizeof(dwData);    
    }
    else if (dwParseType == REG_BINARY) /* Convert the binary data */
    {
        lpbData = convertHexCSVToHex(val_data, &dwLen);
        if (!lpbData)
            return ERROR_INVALID_DATA;    
    }
    else                                /* unknown format */
    {
        fprintf(stderr,"%s: ERROR, unknown data format\n", getAppName());
        return ERROR_INVALID_DATA;
    }

    res = RegSetValueExA(
               currentKeyHandle,
               val_name,
               0,                  /* Reserved */
               dwDataType,
               lpbData,
               dwLen);

    if (dwParseType == REG_BINARY)
        HeapFree(GetProcessHeap(), 0, lpbData);
    return res;
}


/******************************************************************************
 * Open the key
 */
LONG openKey( LPSTR stdInput)
{
    DWORD dwDisp;
    LONG res;

    /* Sanity checks */
    if (stdInput == NULL)
        return ERROR_INVALID_PARAMETER;

    /* Get the registry class */
    if (!getRegClass(stdInput, &currentKeyClass)) /* Sets global variable */
        return ERROR_INVALID_PARAMETER;

    /* Get the key name */
    currentKeyName = getRegKeyName(stdInput); /* Sets global variable */
    if (currentKeyName == NULL)
        return ERROR_INVALID_PARAMETER;

    res = RegCreateKeyExA(
               currentKeyClass,          /* Class     */
               currentKeyName,           /* Sub Key   */
               0,                        /* MUST BE 0 */
               NULL,                     /* object type */
               REG_OPTION_NON_VOLATILE,  /* option, REG_OPTION_NON_VOLATILE ... */
               KEY_ALL_ACCESS,           /* access mask, KEY_ALL_ACCESS */
               NULL,                     /* security attribute */
               &currentKeyHandle,        /* result */
               &dwDisp);                 /* disposition, REG_CREATED_NEW_KEY or
                                                        REG_OPENED_EXISTING_KEY */

    if (res == ERROR_SUCCESS)
        bTheKeyIsOpen = TRUE;

    return res;

}

/******************************************************************************
 * Extracts from [HKEY\some\key\path] or HKEY\some\key\path types of line
 * the key name (what starts after the first '\')
 */
LPSTR getRegKeyName(LPSTR lpLine)
{
    LPSTR keyNameBeg;
    char  lpLineCopy[KEY_MAX_LEN];

    if (lpLine == NULL)
        return NULL;

    strcpy(lpLineCopy, lpLine);

    keyNameBeg = strchr(lpLineCopy, '\\');    /* The key name start by '\' */
    if (keyNameBeg) {
        keyNameBeg++;
        if (lpLine[0] == '[') /* need to find matching ']' */
        {
            LPSTR keyNameEnd;

            keyNameEnd = strrchr(lpLineCopy, ']');
            if (keyNameEnd) {
                *keyNameEnd = '\0';               /* remove ']' from the key name */
            }
        }
    } else {
        keyNameBeg = lpLineCopy + strlen(lpLineCopy); /* branch - empty string */
    }
    currentKeyName = HeapAlloc(GetProcessHeap(), 0, strlen(keyNameBeg) + 1);
    CHECK_ENOUGH_MEMORY(currentKeyName);
    strcpy(currentKeyName, keyNameBeg);
    return currentKeyName;
}

/******************************************************************************
 * Extracts from [HKEY\some\key\path] or HKEY\some\key\path types of line
 * the key class (what ends before the first '\')
 */
BOOL getRegClass(LPSTR lpClass, HKEY* hkey)
{
    LPSTR classNameEnd;
    LPSTR classNameBeg;
    unsigned int i;

    char  lpClassCopy[KEY_MAX_LEN];

    if (lpClass == NULL)
        return FALSE;

    lstrcpynA(lpClassCopy, lpClass, KEY_MAX_LEN);

    classNameEnd  = strchr(lpClassCopy, '\\');    /* The class name ends by '\' */
    if (!classNameEnd)                            /* or the whole string */
    {
        classNameEnd = lpClassCopy + strlen(lpClassCopy);
        if (classNameEnd[-1] == ']')
        {
            classNameEnd--;
        }
    }
    *classNameEnd = '\0';                       /* Isolate the class name */
    if (lpClassCopy[0] == '[') {
        classNameBeg = lpClassCopy + 1;
    } else {
        classNameBeg = lpClassCopy;
    }

    for (i = 0; i < REG_CLASS_NUMBER; i++) {
        if (!strcmp(classNameBeg, reg_class_names[i])) {
            *hkey = reg_class_keys[i];
            return TRUE;
        }
    }
    return FALSE;
}

/******************************************************************************
 * Close the currently opened key.
 */
void closeKey(void)
{
    RegCloseKey(currentKeyHandle);

    HeapFree(GetProcessHeap(), 0, currentKeyName); /* Allocated by getKeyName */

    bTheKeyIsOpen    = FALSE;

    currentKeyName   = NULL;
    currentKeyClass  = 0;
    currentKeyHandle = 0;
}

/******************************************************************************
 * This function is the main entry point to the setValue type of action.  It
 * receives the currently read line and dispatch the work depending on the
 * context.
 */
void doSetValue(LPSTR stdInput)
{
    /*
     * We encountered the end of the file, make sure we
     * close the opened key and exit
     */
    if (stdInput == NULL) {
        if (bTheKeyIsOpen != FALSE)
            closeKey();

        return;
    }

    if      ( stdInput[0] == '[')      /* We are reading a new key */
    {
        if ( bTheKeyIsOpen != FALSE )
            closeKey();                    /* Close the previous key before */

        /* delete the key if we encounter '-' at the start of reg key */
        if ( stdInput[1] == '-')
        {
            int last_chr = strlen(stdInput) - 1;

            /* skip leading "[-" and get rid of trailing "]" */
            if (stdInput[last_chr] == ']')
                stdInput[last_chr] = '\0';
            delete_registry_key(stdInput+2);
            return;
        }

        if ( openKey(stdInput) != ERROR_SUCCESS )
            fprintf(stderr,"%s: setValue failed to open key %s\n",
                    getAppName(), stdInput);
    } else if( ( bTheKeyIsOpen ) &&
               (( stdInput[0] == '@') || /* reading a default @=data pair */
                ( stdInput[0] == '\"'))) /* reading a new value=data pair */
    {
        processSetValue(stdInput);
    } else                               /* since we are assuming that the */
    {                                  /* file format is valid we must   */
        if ( bTheKeyIsOpen )             /* be reading a blank line which  */
            closeKey();                    /* indicate end of this key processing */
    }
}

/******************************************************************************
 * This function is the main entry point to the deleteValue type of action.  It
 * receives the currently read line and dispatch the work depending on the
 * context.
 */
void doDeleteValue(LPSTR line)
{
    UNREFERENCED_PARAMETER(line);
    fprintf(stderr,"%s: deleteValue not yet implemented\n", getAppName());
}

/******************************************************************************
 * This function is the main entry point to the deleteKey type of action.  It
 * receives the currently read line and dispatch the work depending on the
 * context.
 */
void doDeleteKey(LPSTR line)
{
    UNREFERENCED_PARAMETER(line);
    fprintf(stderr,"%s: deleteKey not yet implemented\n", getAppName());
}

/******************************************************************************
 * This function is the main entry point to the createKey type of action.  It
 * receives the currently read line and dispatch the work depending on the
 * context.
 */
void doCreateKey(LPSTR line)
{
    UNREFERENCED_PARAMETER(line);
    fprintf(stderr,"%s: createKey not yet implemented\n", getAppName());
}

/******************************************************************************
 * This function is a wrapper for the setValue function.  It prepares the
 * land and clean the area once completed.
 * Note: this function modifies the line parameter.
 *
 * line - registry file unwrapped line. Should have the registry value name and
 *      complete registry value data.
 */
void processSetValue(LPSTR line)
{
    LPSTR val_name;                   /* registry value name   */
    LPSTR val_data;                   /* registry value data   */

    int line_idx = 0;                 /* current character under analysis */
    LONG res;

    /* get value name */
    if (line[line_idx] == '@' && line[line_idx + 1] == '=') {
        line[line_idx] = '\0';
        val_name = line;
        line_idx++;
    } else if (line[line_idx] == '\"') {
        line_idx++;
        val_name = line + line_idx;
        while (TRUE) {
            /* check if the line is unterminated (otherwise it may loop forever!) */
            if (line[line_idx] == '\0') {
                fprintf(stderr,"Warning! unrecognized line:\n%s\n", line);
                return;
            } else
            if (line[line_idx] == '\\')   /* skip escaped character */
            {
                line_idx += 2;
            } else {
                if (line[line_idx] == '\"') {
                    line[line_idx] = '\0';
                    line_idx++;
                    break;
                } else {
                    line_idx++;
                }
            }
        }
        if (line[line_idx] != '=') {
            line[line_idx] = '\"';
            fprintf(stderr,"Warning! unrecognized line:\n%s\n", line);
            return;
        }

    } else {
        fprintf(stderr,"Warning! unrecognized line:\n%s\n", line);
        return;
    }
    line_idx++;                   /* skip the '=' character */
    val_data = line + line_idx;

    REGPROC_unescape_string(val_name);
    res = setValue(val_name, val_data);
    if ( res != ERROR_SUCCESS )
        fprintf(stderr,"%s: ERROR Key %s not created. Value: %s, Data: %s\n",
                getAppName(),
                currentKeyName,
                val_name,
                val_data);
}

/******************************************************************************
 * Calls command for each line of a registry file.
 * Correctly processes comments (in # form), line continuation.
 *
 * Parameters:
 *   in - input stream to read from
 *   command - command to be called for each line
 */
void processRegLines(FILE *in, CommandAPI command)
{
    LPSTR line           = NULL;  /* line read from input stream */
    size_t lineSize       = REG_VAL_BUF_SIZE;

    line = HeapAlloc(GetProcessHeap(), 0, lineSize);
    CHECK_ENOUGH_MEMORY(line);

    while (!feof(in)) {
        LPSTR s; /* The pointer into line for where the current fgets should read */
        s = line;
        for (;;) {
            size_t size_remaining;
            int size_to_get;
            char *s_eol; /* various local uses */

            /* Do we need to expand the buffer ? */
            assert (s >= line && s <= line + lineSize);
            size_remaining = lineSize - (s-line);
            if (size_remaining < 2) /* room for 1 character and the \0 */
            {
                char *new_buffer;
                size_t new_size = lineSize + REG_VAL_BUF_SIZE;
                if (new_size > lineSize) /* no arithmetic overflow */
                    new_buffer = HeapReAlloc (GetProcessHeap(), 0, line, new_size);
                else
                    new_buffer = NULL;
                CHECK_ENOUGH_MEMORY(new_buffer);
                line = new_buffer;
                s = line + lineSize - size_remaining;
                lineSize = new_size;
                size_remaining = lineSize - (s-line);
            }

            /* Get as much as possible into the buffer, terminated either by
             * eof, error, eol or getting the maximum amount.  Abort on error.
             */
            size_to_get = (int) (size_remaining > INT_MAX ? INT_MAX : size_remaining);
            if (NULL == fgets (s, size_to_get, in)) {
                if (ferror(in)) {
                    perror ("While reading input");
                    exit (IO_ERROR);
                } else {
                    assert (feof(in));
                    *s = '\0';
                    /* It is not clear to me from the definition that the
                     * contents of the buffer are well defined on detecting
                     * an eof without managing to read anything.
                     */
                }
            }

            /* If we didn't read the eol nor the eof go around for the rest */
            s_eol = strchr (s, '\n');
            if (!feof (in) && !s_eol) {
                s = strchr (s, '\0');
                /* It should be s + size_to_get - 1 but this is safer */
                continue;
            }

            /* If it is a comment line then discard it and go around again */
            if (line [0] == '#') {
                s = line;
                continue;
            }

            /* Remove any line feed.  Leave s_eol on the \0 */
            if (s_eol) {
                *s_eol = '\0';
                if (s_eol > line && *(s_eol-1) == '\r')
                    *--s_eol = '\0';
            } else
                s_eol = strchr (s, '\0');

            /* If there is a concatenating \\ then go around again */
            if (s_eol > line && *(s_eol-1) == '\\') {
                int c;
                s = s_eol-1;
                /* The following error protection could be made more self-
                 * correcting but I thought it not worth trying.
                 */
                if ((c = fgetc (in)) == EOF || c != ' ' ||
                        (c = fgetc (in)) == EOF || c != ' ')
                    fprintf(stderr,"%s: ERROR - invalid continuation.\n",
                            getAppName());
                continue;
            }

            break; /* That is the full virtual line */
        }

        command(line);
    }
    command(NULL);

    HeapFree(GetProcessHeap(), 0, line);
}

/******************************************************************************
 * This function is the main entry point to the registerDLL action.  It
 * receives the currently read line, then loads and registers the requested DLLs
 */
void doRegisterDLL(LPSTR stdInput)
{
    HMODULE theLib = 0;
    UINT retVal = 0;

    /* Check for valid input */
    if (stdInput == NULL)
        return;

    /* Load and register the library, then free it */
    theLib = LoadLibraryA(stdInput);
    if (theLib) {
        FARPROC lpfnDLLRegProc = GetProcAddress(theLib, "DllRegisterServer");
        if (lpfnDLLRegProc)
            retVal = (*lpfnDLLRegProc)();
        else
            fprintf(stderr,"%s: Couldn't find DllRegisterServer proc in '%s'.\n",
                    getAppName(), stdInput);

        if (retVal != S_OK)
            fprintf(stderr,"%s: DLLRegisterServer error 0x%x in '%s'.\n",
                    getAppName(), retVal, stdInput);

        FreeLibrary(theLib);
    } else {
        fprintf(stderr,"%s: Could not load DLL '%s'.\n", getAppName(), stdInput);
    }
}

/******************************************************************************
 * This function is the main entry point to the unregisterDLL action.  It
 * receives the currently read line, then loads and unregisters the requested DLLs
 */
void doUnregisterDLL(LPSTR stdInput)
{
    HMODULE theLib = 0;
    UINT retVal = 0;

    /* Check for valid input */
    if (stdInput == NULL)
        return;

    /* Load and unregister the library, then free it */
    theLib = LoadLibraryA(stdInput);
    if (theLib) {
        FARPROC lpfnDLLRegProc = GetProcAddress(theLib, "DllUnregisterServer");
        if (lpfnDLLRegProc)
            retVal = (*lpfnDLLRegProc)();
        else
            fprintf(stderr,"%s: Couldn't find DllUnregisterServer proc in '%s'.\n",
                    getAppName(), stdInput);

        if (retVal != S_OK)
            fprintf(stderr,"%s: DLLUnregisterServer error 0x%x in '%s'.\n",
                    getAppName(), retVal, stdInput);

        FreeLibrary(theLib);
    } else {
        fprintf(stderr,"%s: Could not load DLL '%s'.\n", getAppName(), stdInput);
    }
}

/****************************************************************************
 * REGPROC_print_error
 *
 * Print the message for GetLastError
 */

static void REGPROC_print_error(void)
{
    LPVOID lpMsgBuf;
    DWORD error_code;
    int status;

    error_code = GetLastError ();
    status = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL, error_code, 0, (LPTSTR) &lpMsgBuf, 0, NULL);
    if (!status) {
        fprintf(stderr,"%s: Cannot display message for error %ld, status %ld\n",
                getAppName(), error_code, GetLastError());
        exit(1);
    }
    puts(lpMsgBuf);
    LocalFree((HLOCAL)lpMsgBuf);
    exit(1);
}

/******************************************************************************
 * Checks whether the buffer has enough room for the string or required size.
 * Resizes the buffer if necessary.
 *
 * Parameters:
 * buffer - pointer to a buffer for string
 * len - current length of the buffer in characters.
 * required_len - length of the string to place to the buffer in characters.
 *   The length does not include the terminating null character.
 */
static void REGPROC_resize_char_buffer(CHAR **buffer, DWORD *len, DWORD required_len)
{
    required_len++;
    if (required_len > *len) {
        *len = required_len;
        if (!*buffer)
            *buffer = HeapAlloc(GetProcessHeap(), 0, *len * sizeof(**buffer));
        else
            *buffer = HeapReAlloc(GetProcessHeap(), 0, *buffer, *len * sizeof(**buffer));
        CHECK_ENOUGH_MEMORY(*buffer);
    }
}

/******************************************************************************
 * Prints string str to file
 */
static void REGPROC_export_string(FILE *file, CHAR *str)
{
    size_t len = strlen(str);
    size_t i;

    /* escaping characters */
    for (i = 0; i < len; i++) {
        CHAR c = str[i];
        switch (c) {
        case '\\':
            fputs("\\\\", file);
            break;
        case '\"':
            fputs("\\\"", file);
            break;
        case '\n':
            fputs("\\\n", file);
            break;
        default:
            fputc(c, file);
            break;
        }
    }
}

/******************************************************************************
 * Writes contents of the registry key to the specified file stream.
 *
 * Parameters:
 * file - writable file stream to export registry branch to.
 * key - registry branch to export.
 * reg_key_name_buf - name of the key with registry class.
 *      Is resized if necessary.
 * reg_key_name_len - length of the buffer for the registry class in characters.
 * val_name_buf - buffer for storing value name.
 *      Is resized if necessary.
 * val_name_len - length of the buffer for storing value names in characters.
 * val_buf - buffer for storing values while extracting.
 *      Is resized if necessary.
 * val_size - size of the buffer for storing values in bytes.
 */
static void export_hkey(FILE *file, HKEY key,
                 CHAR **reg_key_name_buf, DWORD *reg_key_name_len,
                 CHAR **val_name_buf, DWORD *val_name_len,
                 BYTE **val_buf, DWORD *val_size)
{
    DWORD max_sub_key_len;
    DWORD max_val_name_len;
    DWORD max_val_size;
    DWORD curr_len;
    DWORD i;
    BOOL more_data;
    LONG ret;

    /* get size information and resize the buffers if necessary */
    if (RegQueryInfoKey(key, NULL, NULL, NULL, NULL,
                        &max_sub_key_len, NULL,
                        NULL, &max_val_name_len, &max_val_size, NULL, NULL
                       ) != ERROR_SUCCESS) {
        REGPROC_print_error();
    }
    curr_len = (DWORD) strlen(*reg_key_name_buf);
    REGPROC_resize_char_buffer(reg_key_name_buf, reg_key_name_len,
                               max_sub_key_len + curr_len + 1);
    REGPROC_resize_char_buffer(val_name_buf, val_name_len,
                               max_val_name_len);
    if (max_val_size > *val_size) {
        *val_size = max_val_size;
        if (!*val_buf) *val_buf = HeapAlloc(GetProcessHeap(), 0, *val_size);
        else *val_buf = HeapReAlloc(GetProcessHeap(), 0, *val_buf, *val_size);
        CHECK_ENOUGH_MEMORY(val_buf);
    }

    /* output data for the current key */
    fputs("\n[", file);
    fputs(*reg_key_name_buf, file);
    fputs("]\n", file);
    /* print all the values */
    i = 0;
    more_data = TRUE;
    while(more_data) {
        DWORD value_type;
        DWORD val_name_len1 = *val_name_len;
        DWORD val_size1 = *val_size;
        ret = RegEnumValueA(key, i, *val_name_buf, &val_name_len1, NULL,
                            &value_type, *val_buf, &val_size1);
        if (ret != ERROR_SUCCESS) {
            more_data = FALSE;
            if (ret != ERROR_NO_MORE_ITEMS) {
                REGPROC_print_error();
            }
        } else {
            i++;

            if ((*val_name_buf)[0]) {
                fputs("\"", file);
                REGPROC_export_string(file, *val_name_buf);
                fputs("\"=", file);
            } else {
                fputs("@=", file);
            }

            switch (value_type) {
            case REG_SZ:
            case REG_EXPAND_SZ:
                fputs("\"", file);
                REGPROC_export_string(file, (char*) *val_buf);
                fputs("\"\n", file);
                break;

            case REG_DWORD:
                fprintf(file, "dword:%08lx\n", *((DWORD *)*val_buf));
                break;

            default:
                fprintf(stderr,"%s: warning - unsupported registry format '%ld', "
                        "treat as binary\n",
                        getAppName(), value_type);
                fprintf(stderr,"key name: \"%s\"\n", *reg_key_name_buf);
                fprintf(stderr,"value name:\"%s\"\n\n", *val_name_buf);
                /* falls through */
            case REG_MULTI_SZ:
                /* falls through */
            case REG_BINARY: {
                    DWORD i1;
                    const CHAR *hex_prefix;
                    CHAR buf[20];
                    int cur_pos;

                    if (value_type == REG_BINARY) {
                        hex_prefix = "hex:";
                    } else {
                        hex_prefix = buf;
                        sprintf(buf, "hex(%ld):", value_type);
                    }

                    /* position of where the next character will be printed */
                    /* NOTE: yes, strlen("hex:") is used even for hex(x): */
                    cur_pos = (int) (strlen("\"\"=") + strlen("hex:") +
                              strlen(*val_name_buf));

                    fputs(hex_prefix, file);
                    for (i1 = 0; i1 < val_size1; i1++) {
                        fprintf(file, "%02x", (unsigned int)(*val_buf)[i1]);
                        if (i1 + 1 < val_size1) {
                            fputs(",", file);
                        }
                        cur_pos += 3;

                        /* wrap the line */
                        if (cur_pos > REG_FILE_HEX_LINE_LEN) {
                            fputs("\\\n  ", file);
                            cur_pos = 2;
                        }
                    }
                    fputs("\n", file);
                    break;
                }
            }
        }
    }

    i = 0;
    more_data = TRUE;
    (*reg_key_name_buf)[curr_len] = '\\';
    while(more_data) {
        DWORD buf_len = *reg_key_name_len - curr_len;

        ret = RegEnumKeyExA(key, i, *reg_key_name_buf + curr_len + 1, &buf_len,
                            NULL, NULL, NULL, NULL);
        if (ret != ERROR_SUCCESS && ret != ERROR_MORE_DATA) {
            more_data = FALSE;
            if (ret != ERROR_NO_MORE_ITEMS) {
                REGPROC_print_error();
            }
        } else {
            HKEY subkey;

            i++;
            if (RegOpenKeyA(key, *reg_key_name_buf + curr_len + 1,
                            &subkey) == ERROR_SUCCESS) {
                export_hkey(file, subkey, reg_key_name_buf, reg_key_name_len,
                            val_name_buf, val_name_len, val_buf, val_size);
                RegCloseKey(subkey);
            } else {
                REGPROC_print_error();
            }
        }
    }
    (*reg_key_name_buf)[curr_len] = '\0';
}

/******************************************************************************
 * Open file for export.
 */
static FILE *REGPROC_open_export_file(const TCHAR *file_name)
{
    FILE *file = _tfopen(file_name, _T("w"));
    if (!file) {
        perror("");
/*      fprintf(stderr,"%s: Can't open file \"%s\"\n", getAppName(), file_name);*/
        exit(1);
    }
    fputs("REGEDIT4\n", file);
    return file;
}

/******************************************************************************
 * Writes contents of the registry key to the specified file stream.
 *
 * Parameters:
 * file_name - name of a file to export registry branch to.
 * reg_key_name - registry branch to export. The whole registry is exported if
 *      reg_key_name is NULL or contains an empty string.
 */
BOOL export_registry_key(const TCHAR *file_name, CHAR *reg_key_name)
{
    HKEY reg_key_class;

    CHAR *reg_key_name_buf;
    CHAR *val_name_buf;
    BYTE *val_buf;
    DWORD reg_key_name_len = KEY_MAX_LEN;
    DWORD val_name_len = KEY_MAX_LEN;
    DWORD val_size = REG_VAL_BUF_SIZE;
    FILE *file = NULL;

    reg_key_name_buf = HeapAlloc(GetProcessHeap(), 0,
                                 reg_key_name_len  * sizeof(*reg_key_name_buf));
    val_name_buf = HeapAlloc(GetProcessHeap(), 0,
                             val_name_len * sizeof(*val_name_buf));
    val_buf = HeapAlloc(GetProcessHeap(), 0, val_size);
    CHECK_ENOUGH_MEMORY(reg_key_name_buf && val_name_buf && val_buf);

    if (reg_key_name && reg_key_name[0]) {
        CHAR *branch_name;
        HKEY key;

        REGPROC_resize_char_buffer(&reg_key_name_buf, &reg_key_name_len,
                                   (DWORD) strlen(reg_key_name));
        strcpy(reg_key_name_buf, reg_key_name);

        /* open the specified key */
        if (!getRegClass(reg_key_name, &reg_key_class)) {
            fprintf(stderr,"%s: Incorrect registry class specification in '%s'\n",
                    getAppName(), reg_key_name);
            exit(1);
        }
        branch_name = getRegKeyName(reg_key_name);
        CHECK_ENOUGH_MEMORY(branch_name);
        if (!branch_name[0]) {
            /* no branch - registry class is specified */
            file = REGPROC_open_export_file(file_name);
            export_hkey(file, reg_key_class,
                        &reg_key_name_buf, &reg_key_name_len,
                        &val_name_buf, &val_name_len,
                        &val_buf, &val_size);
        } else if (RegOpenKeyA(reg_key_class, branch_name, &key) == ERROR_SUCCESS) {
            file = REGPROC_open_export_file(file_name);
            export_hkey(file, key,
                        &reg_key_name_buf, &reg_key_name_len,
                        &val_name_buf, &val_name_len,
                        &val_buf, &val_size);
            RegCloseKey(key);
        } else {
            fprintf(stderr,"%s: Can't export. Registry key '%s' does not exist!\n",
                    getAppName(), reg_key_name);
            REGPROC_print_error();
        }
        HeapFree(GetProcessHeap(), 0, branch_name);
    } else {
        unsigned int i;

        /* export all registry classes */
        file = REGPROC_open_export_file(file_name);
        for (i = 0; i < REG_CLASS_NUMBER; i++) {
            /* do not export HKEY_CLASSES_ROOT */
            if (reg_class_keys[i] != HKEY_CLASSES_ROOT &&
                    reg_class_keys[i] != HKEY_CURRENT_USER &&
                    reg_class_keys[i] != HKEY_CURRENT_CONFIG &&
                    reg_class_keys[i] != HKEY_DYN_DATA) {
                strcpy(reg_key_name_buf, reg_class_names[i]);
                export_hkey(file, reg_class_keys[i],
                            &reg_key_name_buf, &reg_key_name_len,
                            &val_name_buf, &val_name_len,
                            &val_buf, &val_size);
            }
        }
    }

    if (file) {
        fclose(file);
    }
    HeapFree(GetProcessHeap(), 0, val_buf);
    return TRUE;
}

/******************************************************************************
 * Reads contents of the specified file into the registry.
 */
BOOL import_registry_file(LPTSTR filename)
{
    FILE* reg_file = _tfopen(filename, _T("r"));

    if (reg_file) {
        unsigned char ch1 = fgetc(reg_file);
        unsigned char ch2 = fgetc(reg_file);

        /* detect UTF-16.LE or UTF-16.BE format */
        if ((ch1 == 0xff && ch2 == 0xfe) ||
            (ch1 == 0xfe && ch2 == 0xff)) {
            /* TODO: implement support for UNICODE files! */
        } else {
            /* restore read point to the first line */
            fseek(reg_file, 0L, SEEK_SET);
            processRegLines(reg_file, doSetValue);
        }
        fclose(reg_file);
        return TRUE;
    }
    return FALSE;
}

/******************************************************************************
 * Recursive function which removes the registry key with all subkeys.
 */
static void delete_branch(HKEY key,
                   CHAR **reg_key_name_buf, DWORD *reg_key_name_len)
{
    HKEY branch_key;
    DWORD max_sub_key_len;
    DWORD subkeys;
    DWORD curr_len;
    LONG ret;
    long int i;

    if (RegOpenKeyA(key, *reg_key_name_buf, &branch_key) != ERROR_SUCCESS) {
        REGPROC_print_error();
    }

    /* get size information and resize the buffers if necessary */
    if (RegQueryInfoKey(branch_key, NULL, NULL, NULL,
                        &subkeys, &max_sub_key_len,
                        NULL, NULL, NULL, NULL, NULL, NULL
                       ) != ERROR_SUCCESS) {
        REGPROC_print_error();
    }
    curr_len = (DWORD) strlen(*reg_key_name_buf);
    REGPROC_resize_char_buffer(reg_key_name_buf, reg_key_name_len,
                               max_sub_key_len + curr_len + 1);

    (*reg_key_name_buf)[curr_len] = '\\';
    for (i = subkeys - 1; i >= 0; i--) {
        DWORD buf_len = *reg_key_name_len - curr_len;

        ret = RegEnumKeyExA(branch_key, i, *reg_key_name_buf + curr_len + 1,
                            &buf_len, NULL, NULL, NULL, NULL);
        if (ret != ERROR_SUCCESS &&
                ret != ERROR_MORE_DATA &&
                ret != ERROR_NO_MORE_ITEMS) {
            REGPROC_print_error();
        } else {
            delete_branch(key, reg_key_name_buf, reg_key_name_len);
        }
    }
    (*reg_key_name_buf)[curr_len] = '\0';
    RegCloseKey(branch_key);
    RegDeleteKeyA(key, *reg_key_name_buf);
}

/******************************************************************************
 * Removes the registry key with all subkeys. Parses full key name.
 *
 * Parameters:
 * reg_key_name - full name of registry branch to delete. Ignored if is NULL,
 *      empty, points to register key class, does not exist.
 */
void delete_registry_key(CHAR *reg_key_name)
{
    CHAR *branch_name;
    DWORD branch_name_len;
    HKEY reg_key_class;
    HKEY branch_key;

    if (!reg_key_name || !reg_key_name[0])
        return;
    /* open the specified key */
    if (!getRegClass(reg_key_name, &reg_key_class)) {
        fprintf(stderr,"%s: Incorrect registry class specification in '%s'\n",
                getAppName(), reg_key_name);
        exit(1);
    }
    branch_name = getRegKeyName(reg_key_name);
    CHECK_ENOUGH_MEMORY(branch_name);
    branch_name_len = (DWORD) strlen(branch_name);
    if (!branch_name[0]) {
        fprintf(stderr,"%s: Can't delete registry class '%s'\n",
                getAppName(), reg_key_name);
        exit(1);
    }
    if (RegOpenKeyA(reg_key_class, branch_name, &branch_key) == ERROR_SUCCESS) {
        /* check whether the key exists */
        RegCloseKey(branch_key);
        delete_branch(reg_key_class, &branch_name, &branch_name_len);
    }
    HeapFree(GetProcessHeap(), 0, branch_name);
}

/******************************************************************************
 * Sets the application name. Then application name is used in the error
 * reporting.
 */
void setAppName(const CHAR *name)
{
    app_name = name;
}

const CHAR *getAppName(void)
{
    return app_name;
}

LONG RegCopyKey(HKEY hDestKey, LPCTSTR lpDestSubKey, HKEY hSrcKey, LPCTSTR lpSrcSubKey)
{
    LONG lResult;
    DWORD dwDisposition;
    HKEY hDestSubKey = NULL;
    HKEY hSrcSubKey = NULL;
    DWORD dwIndex, dwType, cbName, cbData;
    TCHAR szSubKey[256];
    TCHAR szValueName[256];
    BYTE szValueData[512];

    FILETIME ft;

    /* open the source subkey, if specified */
    if (lpSrcSubKey)
    {
        lResult = RegOpenKeyEx(hSrcKey, lpSrcSubKey, 0, KEY_ALL_ACCESS, &hSrcSubKey);
        if (lResult)
            goto done;
        hSrcKey = hSrcSubKey;
    }

    /* create the destination subkey */
    lResult = RegCreateKeyEx(hDestKey, lpDestSubKey, 0, NULL, 0, KEY_WRITE, NULL,
        &hDestSubKey, &dwDisposition);
    if (lResult)
        goto done;

    /* copy all subkeys */
    dwIndex = 0;
    do
    {
        cbName = sizeof(szSubKey) / sizeof(szSubKey[0]);
        lResult = RegEnumKeyEx(hSrcKey, dwIndex++, szSubKey, &cbName, NULL, NULL, NULL, &ft);
        if (lResult == ERROR_SUCCESS)
        {
            lResult = RegCopyKey(hDestSubKey, szSubKey, hSrcKey, szSubKey);
            if (lResult)
                goto done;
        }
    }
    while(lResult == ERROR_SUCCESS);

    /* copy all subvalues */
    dwIndex = 0;
    do
    {
        cbName = sizeof(szValueName) / sizeof(szValueName[0]);
        cbData = sizeof(szValueData) / sizeof(szValueData[0]);
        lResult = RegEnumValue(hSrcKey, dwIndex++, szValueName, &cbName, NULL, &dwType, szValueData, &cbData);
        if (lResult == ERROR_SUCCESS)
        {
            lResult = RegSetValueEx(hDestSubKey, szValueName, 0, dwType, szValueData, cbData);
            if (lResult)
                goto done;
        }
    }
    while(lResult == ERROR_SUCCESS);

    lResult = ERROR_SUCCESS;

done:
    if (hSrcSubKey)
        RegCloseKey(hSrcSubKey);
    if (hDestSubKey)
        RegCloseKey(hDestSubKey);
    if (lResult != ERROR_SUCCESS)
        SHDeleteKey(hDestKey, lpDestSubKey);
    return lResult;

}

LONG RegMoveKey(HKEY hDestKey, LPCTSTR lpDestSubKey, HKEY hSrcKey, LPCTSTR lpSrcSubKey)
{
    LONG lResult;

    if (!lpSrcSubKey)
        return ERROR_INVALID_FUNCTION;

    lResult = RegCopyKey(hDestKey, lpDestSubKey, hSrcKey, lpSrcSubKey);
    if (lResult == ERROR_SUCCESS)
        SHDeleteKey(hSrcKey, lpSrcSubKey);

    return lResult;
}

LONG RegRenameKey(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpNewName)
{
    LPCTSTR s;
    LPTSTR lpNewSubKey = NULL;
    LONG Ret = 0;

	if (!lpSubKey)
		return Ret;

    s = _tcsrchr(lpSubKey, _T('\\'));
    if (s)
    {
        s++;
        lpNewSubKey = (LPTSTR) HeapAlloc(GetProcessHeap(), 0, (s - lpSubKey + _tcslen(lpNewName) + 1) * sizeof(TCHAR));
        if (lpNewSubKey != NULL)
        {
            memcpy(lpNewSubKey, lpSubKey, (s - lpSubKey) * sizeof(TCHAR));
            _tcscpy(lpNewSubKey + (s - lpSubKey), lpNewName);
            lpNewName = lpNewSubKey;
        }
        else
            return ERROR_NOT_ENOUGH_MEMORY;
    }

    Ret = RegMoveKey(hKey, lpNewName, hKey, lpSubKey);

    if (lpNewSubKey)
    {
        HeapFree(GetProcessHeap(), 0, lpNewSubKey);
    }
    return Ret;
}

LONG RegRenameValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpDestValue, LPCTSTR lpSrcValue)
{
    LONG lResult;
    HKEY hSubKey = NULL;
    DWORD dwType, cbData;
    BYTE data[512];

    if (lpSubKey)
    {
        lResult = RegOpenKey(hKey, lpSubKey, &hSubKey);
        if (lResult != ERROR_SUCCESS)
            goto done;
        hKey = hSubKey;
    }

    cbData = sizeof(data);
    lResult = RegQueryValueEx(hKey, lpSrcValue, NULL, &dwType, data, &cbData);
    if (lResult != ERROR_SUCCESS)
        goto done;

    lResult = RegSetValueEx(hKey, lpDestValue, 0, dwType, data, cbData);
    if (lResult != ERROR_SUCCESS)
        goto done;

    RegDeleteValue(hKey, lpSrcValue);

done:
    if (hSubKey)
        RegCloseKey(hSubKey);
    return lResult;
}

LONG RegQueryStringValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPTSTR pszBuffer, DWORD dwBufferLen)
{
    LONG lResult;
    HKEY hSubKey = NULL;
    DWORD cbData, dwType;

    if (lpSubKey)
    {
        lResult = RegOpenKey(hKey, lpSubKey, &hSubKey);
        if (lResult != ERROR_SUCCESS)
            goto done;
        hKey = hSubKey;
    }

    cbData = (dwBufferLen - 1) * sizeof(*pszBuffer);
    lResult = RegQueryValueEx(hKey, lpValueName, NULL, &dwType, (LPBYTE) pszBuffer, &cbData);
    if (lResult != ERROR_SUCCESS)
        goto done;
    if (dwType != REG_SZ)
    {
        lResult = -1;
        goto done;
    }

    pszBuffer[cbData / sizeof(*pszBuffer)] = '\0';

done:
    if (lResult != ERROR_SUCCESS)
        pszBuffer[0] = '\0';
    if (hSubKey)
        RegCloseKey(hSubKey);
    return lResult;
}

/******************************************************************************
 * Key naming and parsing
 */

BOOL RegKeyGetName(LPTSTR pszDest, size_t iDestLength, HKEY hRootKey, LPCTSTR lpSubKey)
{
    LPCTSTR pszRootKey;

    if (hRootKey == HKEY_CLASSES_ROOT)
        pszRootKey = TEXT("HKEY_CLASSES_ROOT");
    else if (hRootKey == HKEY_CURRENT_USER)
        pszRootKey = TEXT("HKEY_CURRENT_USER");
    else if (hRootKey == HKEY_LOCAL_MACHINE)
        pszRootKey = TEXT("HKEY_LOCAL_MACHINE");
    else if (hRootKey == HKEY_USERS)
        pszRootKey = TEXT("HKEY_USERS");
    else if (hRootKey == HKEY_CURRENT_CONFIG)
        pszRootKey = TEXT("HKEY_CURRENT_CONFIG");
    else if (hRootKey == HKEY_DYN_DATA)
        pszRootKey = TEXT("HKEY_DYN_DATA");
    else
        return FALSE;

    if (lpSubKey[0])
        _sntprintf(pszDest, iDestLength, TEXT("%s\\%s"), pszRootKey, lpSubKey);
    else
        _sntprintf(pszDest, iDestLength, TEXT("%s"), pszRootKey);
    return TRUE;
}


