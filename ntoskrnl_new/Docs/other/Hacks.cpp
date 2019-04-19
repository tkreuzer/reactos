
extern "C"
int
wctomb(
   char *mbchar,
   wchar_t wchar)
{
    *mbchar = (char)wchar;
    return 1;
}


