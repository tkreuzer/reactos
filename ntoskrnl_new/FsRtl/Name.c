
#include <ntoskrnl.h>

BOOLEAN
NTAPI
FsRtlAreNamesEqual(
  __in      PCUNICODE_STRING ConstantNameA,
  __in      PCUNICODE_STRING ConstantNameB,
  __in      BOOLEAN IgnoreCase,
  __in_opt  PCWCH UpcaseTable)
{
    PWCHAR StringA, StringB;
    ULONG CharacterCount;

    /* First check if the sizes match */
    if (ConstantNameA->Length != ConstantNameB->Length)
        return FALSE;

    /* Get the string pointers and character count */
    StringA = ConstantNameA->Buffer;
    StringB = ConstantNameB->Buffer;
    CharacterCount = ConstantNameA->Length / sizeof(WCHAR);

    /* Check if this is a case sensitive search */
    if (!IgnoreCase)
    {
        /* Loop all characters */
        while (CharacterCount-- > 0)
        {
            /* Compare the characters */
            if ((*StringA++) != (*StringB++))
            {
                return FALSE;
            }
        }
    }

    /* This is case insensitive. Is an upcase table given? */
    else if (UpcaseTable)
    {
        /* Loop all characters */
        while (CharacterCount-- > 0)
        {
            /* Compare upcased character, using the given table */
            if (UpcaseTable[*StringA++] != UpcaseTable[*StringB++])
            {
                return FALSE;
            }
        }

        return TRUE;
    }
    else
    {
        /* Loop all characters */
        while (CharacterCount-- > 0)
        {
            /* Compare upcased character, using the system upcase table */
            if (RtlUpcaseUnicodeChar(*StringA++) !=
                RtlUpcaseUnicodeChar(*StringB++))
            {
                return FALSE;
            }
        }
    }

    /* When we got here, then all characters were equal */
    return TRUE;
}

