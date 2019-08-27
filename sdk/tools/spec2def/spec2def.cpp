
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdarg>

using namespace std;

class Spec2Def
{
public:

    Spec2Def(int argc, char* argv[])
    {
        m_Compiler = GCC;
        m_notPrivateNoWarn = false;

        for (int i = 1; i < argc; i++)
        {
            if ((strcmp(argv[i], "--help") == 0) ||
                (strcmp(argv[i], "-h") == 0))
            {
                usage();
            }
            else if (argv[i][1] == 'd' && argv[i][2] == '=')
            {
                m_defFileName = string(argv[i] + 3);
            }
            else if (argv[i][1] == 'l' && argv[i][2] == '=')
            {
                m_libStubFileName = string(argv[i] + 3);
            }
            else if (argv[i][1] == 's' && argv[i][2] == '=')
            {
                m_stubFileName = argv[i] + 3;
            }
            else if (argv[i][1] == 'n' && argv[i][2] == '=')
            {
                m_dllName = string(argv[i] + 3);
            }
            //else if (strncasecmp(argv[i], pszVersionOption, strlen(pszVersionOption)) == 0)
            //{
            //    guOsVersion = strtoul(argv[i] + strlen(pszVersionOption), NULL, 16);
            //}
            else if (strcmp(argv[i], "--implib") == 0)
            {
                m_importLib = true;
            }
            else if (strcmp(argv[i], "--ms") == 0)
            {
                m_Compiler = MSVC;
            }
            else if (strcmp(argv[i], "--no-private-warnings") == 0)
            {
                m_notPrivateNoWarn = true;
            }
            else if (strcmp(argv[i], "--with-tracing") == 0)
            {
                //if (!pszStubFileName)
                //{
                //    fprintf(stderr, "Error: cannot use --with-tracing without -s option.\n");
                //    return -1;
                //}
                //gbTracing = 1;
            }
            else if (argv[i][1] == 'a' && argv[i][2] == '=')
            {
                m_archString = string(argv[i] + 3);
            }
            else if (argv[i][0] == '-')
            {
                throw invalid_argument(string("Unexpected option") + string(argv[i]));
            }
            else
            {
                if (i < (argc - 1))
                {
                    throw invalid_argument("Unexpected additional parameters after spec file.");
                }
                m_specFileName = string(argv[i]);
            }
        }
    }

    void run()
    {
        // parse input file
        parseSpecFile();
        
        // output each file
        if (m_defFileName.size() != 0)
        {

        }
    }

private:

    enum Compiler
    {
        GCC,
        MSVC
    };

    struct Token
    {
        int line;
        int column;
        string str;
    };

    struct Options
    {
        union
        {
            struct
            {
                unsigned isPrivate : 1;
                unsigned isStub : 1;
                unsigned isNoname : 1;
                unsigned isNorelay : 1;
                unsigned isRet64 : 1;
                unsigned isRegister : 1;
            };
            unsigned asUint;
        } flags;
        unsigned versionMask;
    };

    enum CallingConvention
    {
        CC_STUB,
        CC_STDCALL,
        CC_CDECL,
        CC_FASTCALL,
        CC_THISCALL,
        CC_EXTERN,
    };

    enum ArgType
    {
        ARG_LONG,
        ARG_PTR,
        ARG_STR,
        ARG_WSTR,
        ARG_DBL,
        ARG_INT64,
        ARG_INT128,
        ARG_FLOAT
    };

    struct Export
    {
        int ordinal;
        CallingConvention callingConvention;
        Options options;
        string functionName;
        vector<ArgType> arguments;
        int nStackBytes;
        string forwarderName;
    };

    class ParseError : exception
    {
    public:
        explicit ParseError(Token& token, const char *format, ...)
            : m_token(token)
        {
            char buffer[200];
            va_list argList;
            va_start(argList, format);
            vsnprintf(buffer, sizeof(buffer), format, argList);
            va_end(argList);
            m_message = string("ERROR: ") + string(buffer);
        }

        explicit ParseError(const std::string& message) :
            m_message(message)
        {
        }

        virtual ~ParseError() throw ()
        {
        }

        virtual const char* what() const throw ()
        {
            return m_message.c_str();
        }

    protected:
        Token m_token;
        std::string m_message;
    };

    void usage()
    {
        printf("syntax: spec2def [<options> ...] <spec file>\n"
               "Possible options:\n"
               "  -h --help               print this help screen\n"
               "  -l=<file>               generate an asm lib stub\n"
               "  -d=<file>               generate a def file\n"
               "  -s=<file>               generate a stub file\n"
               "  --ms                    MSVC compatibility\n"
               "  -n=<name>               name of the dll\n"
               "  --implib                generate a def file for an import library\n"
               "  --no-private-warnings   suppress warnings about symbols that should be -private\n"
               "  -a=<arch>               set architecture to <arch> (i386, x86_64, arm)\n"
               "  --with-tracing          generate wine-like \"+relay\" trace trampolines (needs -s)\n");
    }

    void parseSpecFile()
    {
        ifstream file(m_specFileName);
        string line;

        m_currentLine = 1;
        while (getline(file, line))
        {
            parseLine(line);
            m_currentLine++;
        }
    }

    void parseLine(string line)
    {
        stringstream lineStream(line);
        Token token;
        Export exp;

        /* Skip empty lines */
        if (!getToken(lineStream, &token))
        {
            return;
        }

        /* Parse ordinal or '@' */
        exp.ordinal = parseOrdinal(token);

        /* Parse the calling convention */
        token = getToken(lineStream);
        if (token.str == "sd") throw ParseError("too bad");
#if 0
        exp.callingConvention = parseCallingConvention(token);

        /* Parse options */
        exp.options.flags.asUint = 0;
        exp.options.versionMask = 0;
        while (getToken(lineStream, &token) && (token.str[0] == '-'))
        {
            ParseOption(token, &exp.options);
        }

        exp.functionName = getToken(lineStream).str;

        /* If the CC is not stub or extern, then parse arguments */
        if ((exp.callingConvention != CC_STUB) &&
            (exp.callingConvention != CC_EXTERN))
        {
            token = getToken(lineStream);
            if (token.str != "(")
            {
                throw ParseError(token, "Expexted '('");
            }

            token = getToken(lineStream);
            if (token.str != "(")
            {
                throw ParseError(token, "Expexted '('");
            }

            token = getToken(lineStream);
            if (token.str != ")")
            {
                throw ParseError(token, "Expexted '('");
            }
        }
#endif
    }

    Token getToken(istream& is)
    {
        Token token;
        char chr;

        token.str.empty();
        token.line = m_currentLine;

        /* Skip leading whitespace */
        do
        {
            if (!is.get(chr))
            {
                token.column = (int)is.tellg();
                return token;
            }
        } while (isspace(chr));

        token.column = (int)is.tellg();

        /* Bail at comment */
        if (chr == '#')
        {
            return token;
        }

        /* Push first char */
        token.str.push_back(chr);

        /* Collect rest of token */
        while (((chr = is.peek()) != EOF) && !isSeparator(chr))
        {
            is.get(chr);
            token.str.push_back(chr);
        }

        return token;
    }

    bool getToken(istream& is, Token* token)
    {
        *token = getToken(is);
        return token->str.size() != 0;
    }

    bool isSeparator(char chr)
    {
        return ((chr <= ',' && chr != '$' && chr != '#') ||
            (chr >= ':' && chr < '?'));
    }

    int parseOrdinal(Token& token)
    {
        if (token.str == "@")
        {
            return -1;
        }

        size_t pos;
        int ordinal = stoul(token.str, &pos);
        if (pos != token.str.size())
        {
            throw ParseError(token, "Invalid ordinal");
        }

        return ordinal;
    }

    CallingConvention parseCallingConvention(Token& token)
    {
        if (token.str == "stub")
            return CC_STUB;
        if (token.str == "stdcall")
            return CC_STDCALL;
        if (token.str == "cdecl")
            return CC_CDECL;
        if (token.str == "fastcall")
            return CC_FASTCALL;
        if (token.str == "thiscall")
            return CC_THISCALL;
        if (token.str == "extern")
            return CC_EXTERN;
        string error = string("Invalid calling convention: ") + token.str;
        throw ParseError(token, error.c_str());
    }

    void ParseOption(Token& token, Options *options)
    {
        if (token.str.compare(0, strlen("-arch="), "-arch=") == 0)
        {
            throw "-arch";
        }
        else if (token.str == "-i386")
        {
            // FIXME
            throw "-i386";
        }
        else if (token.str == "-noname")
        {
            options->flags.isNoname = true;
        }
        else if (token.str == "-norelay")
        {
            options->flags.isNorelay = true;
        }
        else if (token.str == "-ordinal")
        {
            // CHECKME
            throw "-ordinal";
        }
        else if (token.str == "-private")
        {
            options->flags.isPrivate = true;
        }
        else if (token.str == "-register")
        {
            options->flags.isRegister = true;
        }
        else if (token.str == "-ret64")
        {
            options->flags.isRet64 = true;
        }
        else if (token.str == "-stub")
        {
            options->flags.isStub = true;
        }
        else if (token.str.compare(0, strlen("-version="), "-version=") == 0)
        {
            throw "-version";
        }
        else
        {
            throw ParseError(token, "Unrecognized option");
        }
    }

    string m_specFileName;
    string m_defFileName;
    string m_stubFileName;
    string m_libStubFileName;
    string m_dllName;
    bool m_importLib;
    string m_archString;
    Compiler m_Compiler;
    bool m_notPrivateNoWarn;

    int m_currentLine;
};



int
main(
    int argc,
    char* argv[])
{
    try
    {
        Spec2Def spec2def(argc, argv);
        spec2def.run();
    }
    catch (exception ex)
    {
        fprintf(stderr, ex.what());
        return -1;
    }

    return 0;
}
