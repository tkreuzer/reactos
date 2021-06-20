/*
 *  Generates wow64 stubs for nt functions
 *  Usage: genwow64 <header file> <output c++ file>
 */

#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace std;

#if 0
#define TracePrint(Format, ...) fprintf(stderr, Format, __VA_ARGS__)
#else
#define TracePrint(Format, ...)
#endif

bool
IsSpecialCharacter(char x)
{
    return (x == '(') ||
        (x == ')') ||
        (x == '[') ||
        (x == ']') ||
        (x == '{') ||
        (x == '}') ||
        (x == '+') ||
        (x == '-') ||
        (x == '*') ||
        (x == '/') ||
        (x == '%') ||
        (x == '=') ||
        (x == '!') ||
        (x == '~') ||
        (x == '^') ||
        (x == '&') ||
        (x == '?') ||
        (x == ':') ||
        (x == ',') ||
        (x == ';');
}

vector<string>
Tokenize(string &Input)
{
    vector<string> tokens;
    size_t end, start = 0;

    while (start < Input.size())
    {
        // Skip whitespace
        if (isspace(Input[start]))
        {
            start++;
            continue;
        }

        TracePrint("Tokenize start = %u\n", start);

        // Check for multiline comment
        if ((Input[start] == '/') && (Input[start + 1] == '*'))
        {
            TracePrint("Found multiline comment: ");
            // Search for end of the inline comment
            const char *p = strstr(&Input[start + 1], "*/");
            end = p + 2 - Input.c_str();
        }

        // Check for C++ comment
        else if ((Input[start] == '/') && (Input[start + 1] == '/'))
        {
            TracePrint("Found C++ comment: ");
            // Search for end of the line
            const char *p =  strstr(&Input[start + 1], "\n");
            end = p + 1 - Input.c_str();
        }

        // Check for preprocessor command
        else if (Input[start] == '#')
        {
            TracePrint("Found preprocessor command: ");
            // Search for end of the line
            const char *p = strstr(&Input[start + 1], "\n");
            end = p - Input.c_str();
        }

        // Check for string
        else if ((Input[start] == '\"') || (Input[start] == '\''))
        {
            TracePrint("Found stringt ");
            // Search for end of the string
            end = start + 1;
            while ((Input[end] != Input[start]) && (Input[end - 1] != '\\'))
            {
                end++;
            }
            end++;
        }

        // Check for special character
        else if (IsSpecialCharacter(Input[start]))
        {
            TracePrint("Found special charactert: ");
            // Use this character alone
            end = start + 1;
        }

        else
        {
            TracePrint("Found identifier: ");
            // Find end of the token
            end = start + 1;
            while (!isspace(Input[end]) && !IsSpecialCharacter(Input[end]))
            {
                end++;
            }
        }
 
        // Add this token
        tokens.push_back(Input.substr(start, end - start));
        TracePrint("%s\n", Input.substr(start, end - start).c_str());
        start = end;
    }

    return tokens;
}

enum DIRECTION
{
    Dir_In_,
    Dir_Out_,
    Dir_Inout_,
    Dir_Unknown_
};

struct PARAMETER
{
    string Name;
    string Type;
    DIRECTION Direction;
};

struct FUNCTION
{
    string Name;
    vector<PARAMETER> Parameters;
};

bool
ParseNtParameter(vector<string>& Tokens, int& Index, PARAMETER& Parameter)
{
    Parameter.Direction = Dir_Unknown_;

    TracePrint("Checking parameter: '%s', '%s', '%s'\n", Tokens[Index].c_str(), Tokens[Index+1].c_str(), Tokens[Index+2].c_str());

    // Check up to 5 annotations
    for (int i = 0; i < 5; i++)
    {
        if (Tokens[Index] == "_In_")
        {
            Parameter.Direction = Dir_In_;
        }
        else if (Tokens[Index] == "_Out_")
        {
            Parameter.Direction = Dir_Out_;
        }
        else if (Tokens[Index] == "_Out_")
        {
            Parameter.Direction = Dir_Out_;
        }
        else if ((Tokens[Index][0] != '_') ||
                 (Tokens[Index].back() != '_'))
        {
            // FIXME: need to handle all annotations
            break;
        }
        Index++;
    }

    if (Parameter.Direction == Dir_Unknown_)
    {
        return false;
    }

    // Type should be all upper case
    Parameter.Type = Tokens[Index];
    for (int i = 0; i < Parameter.Type.size(); i++)
    {
        if (!isalpha(Parameter.Type[i]) || !isupper(Parameter.Type[i]))
        {
            return false;
        }
    }
    Index++;

    // Now the Name should be all letters and start with
    Parameter.Name = Tokens[Index];
    for (int i = 0; i < Parameter.Type.size(); i++)
    {
        if (!isalpha(Parameter.Type[i]) || !isupper(Parameter.Type[i]))
        {
            return false;
        }
    }
    if (!isupper(Parameter.Type[0]))
    {
        return false;
    }
    Index++;

    // Looks all good
    return true;
}

bool
ParseNtPrototype(vector<string>& Tokens, int& Index, FUNCTION& Function)
{
    // Validate size
    if (Index + 8 >= Tokens.size())
        return false;

    // should start with NTSTATUS
    if (Tokens[Index] != "NTSTATUS")
        return false;

    // Next should be the Nt function name
    if (Tokens[Index + 1].substr(0, 2) != "Nt")
        return false;

    // Now the opening brace
    if (Tokens[Index + 2] != "(")
        return false;

    Function.Name = Tokens[Index + 1];

    TracePrint("Found candidate: %s\n", Function.Name.c_str());

    // now parse the arguments
    Index += 3;
    for (int param = 0; param < 30; param++)
    {
        PARAMETER parameter;

        TracePrint("Checking parameter %u...\n", param);

        if (!ParseNtParameter(Tokens, Index, parameter))
        {
            TracePrint("  Failed to parse parameter.\n");
            return false;
        }

        if ((Tokens[Index] == ")") &&
            (Tokens[Index + 1] == ";"))
        {
            Index += 2;
            Function.Parameters.push_back(parameter);
            break;
        }
        else if (Tokens[Index] != ",")
        {
            TracePrint("  Parameter doesn't end with ','.\n");
            return false;
        }

        Index++;
        Function.Parameters.push_back(parameter);
    }

    TracePrint("Done with function.\n\n");
    return true;
}

const char*
GetDirectionString(DIRECTION Direction)
{
    switch (Direction)
    {
        case Dir_In_: return "Dir_In_";
        case Dir_Out_: return "Dir_Out_";
        case Dir_Inout_: return "Dir_Inout_";
        default: return "Dir_Unknown_";
    }
}

void
GenerateFunctions(
    FILE* File,
    vector<FUNCTION>& Functions)
{
    fprintf(File, "#include \"thunkhelper.hpp\"\n\n");
    for (int i = 0; i < Functions.size(); i++)
    {
        FUNCTION& function = Functions[i];

       // if (function.Name != "NtCompressKey") continue;
        fprintf(stderr, "Genratinng stub for %s\n", function.Name.c_str());

        /* First generate the Parameters */
        fprintf(File, "struct PARAMS32_%s\n{\n", function.Name.c_str());
        for (PARAMETER& param: function.Parameters)
        {
            fprintf(File, "    TYPE32<%s> %s;\n", param.Type.c_str(), param.Name.c_str());
        }
        fprintf(File, "};\n\n");

        /* Next is the cfunction header */
        fprintf(File,
                "NTSTATUS\n"
                "wh%s(PARAMS32_%s *Params32)\n"
                "{\n",
                function.Name.c_str(),
                function.Name.c_str());

        /* Generate converter variables */
        for (int i = 0; i < function.Parameters.size(); i++)
        {
            PARAMETER& param = function.Parameters[i];

            fprintf(File,
                    "    PARAM64<%s, %s> %s(Params32->%s);\n",
                    GetDirectionString(param.Direction),
                    param.Type.c_str(),
                    param.Name.c_str(),
                    param.Name.c_str());
        }

        fprintf(File, "\n    return %s(\n", function.Name.c_str());

        /* Generate converter variables */
        for (int i = 0; i < function.Parameters.size(); i++)
        {
            PARAMETER& param = function.Parameters[i];

            fprintf(File,
                    "        %s%s\n",
                    param.Name.c_str(),
                    (i == (function.Parameters.size() - 1)) ? ");" : ",");
        }

        fprintf(File, "}\n\n");
    }
}

int main(int argc, const char* argv[])
{
    TracePrint("Opening input file...\n");

    /* Open the input file */
    ifstream input(argv[1]);
    string str{ istreambuf_iterator<char>(input),
               istreambuf_iterator<char>() };

    TracePrint("Tokenizing input file...\n");
    vector<string> tokens = Tokenize(str);
    TracePrint("Number of tokens: %u.\n", (int)tokens.size());

    vector<FUNCTION> functions;

    TracePrint("Generating function stubs...\n");

    // Loop the tokens
    for (int i = 0; i < tokens.size() - 4; i++)
    {
        FUNCTION function;

        //fprintf(stderr, "Checking tokens: '%s', '%s', '%s'\n", tokens[i].c_str(), tokens[i + 1].c_str(), tokens[i + 2].c_str());
        if (ParseNtPrototype(tokens, i, function))
        {
            functions.push_back(function);
        }
    }

    /* Open the output file */
    FILE *output = fopen(argv[2], "w");
    if (!output)
    {
        fprintf(stderr, "Could not open output file '%s'\n", argv[2]);
        return -1;
    }

    // Output the functions
    GenerateFunctions(output, functions);

    fclose(output);

    return 0;
}
