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

struct ANNOTATION
{
    DIRECTION Direction;
    string PreSizeParameter;
    string PostSizeParameter;
    bool ByteSize;
    bool DerefPreSizeParameter;
    bool DerefPostSizeParameter;
};

struct PARAMETER
{
    string Name;
    string Type;
    ANNOTATION Annotation;
};

struct FUNCTION
{
    string Name;
    vector<PARAMETER> Parameters;
};

bool
ParseAnnotation(
    string& FunctionName,
    vector<string>& Tokens,
    int& Index,
    ANNOTATION& Annotation)
{
    int indexP1, indexP2, indexEnd = Index;

    fprintf(stderr, "Parsing annotation: %s\n", Tokens[Index].c_str());

    Annotation.PreSizeParameter.clear();
    Annotation.PostSizeParameter.clear();
    Annotation.ByteSize = false;
    Annotation.DerefPreSizeParameter = false;

    if (Tokens[Index].substr(0, 4) == "_In_")
    {
        Annotation.Direction = Dir_In_;

        /* Check for the _reads_ variant */
        if (Tokens[Index].substr(4, 6) == "reads_")
        {
            /* These require 1 parameter */
            if (Tokens[Index + 1] != "(")
            {
                fprintf(stderr, "Annotation %s without parameters\n", Tokens[Index].c_str());
                return false;
            }

            /* Check if the size is in bytes */
            if (Tokens[Index].substr(12, 6) == "bytes_")
            {
                Annotation.ByteSize = true;
            }

            indexP1 = Index + 2;

            /* Check if the parameter is dereferenced */
            if (Tokens[indexP1] == "*")
            {
                Annotation.DerefPreSizeParameter = true;
                indexP1++;
            }

            Annotation.PreSizeParameter = Tokens[indexP1];
            indexEnd = indexP1 + 1;

            /* Validate closing ')' */
            if (Tokens[indexEnd] != ")")
            {
                fprintf(stderr, "Expected ')' got ''\n",
                        Tokens[indexEnd].c_str());
                return false;
            }
        }
    }
    else if (Tokens[Index].substr(0, 5) == "_Out_")
    {
        Annotation.Direction = Dir_Out_;

        /* Check for the _writes_ variant */
        if (Tokens[Index].substr(5, 7) == "writes_")
        {
            /* These require 1 or 2 parameters */
            if (Tokens[Index + 1] != "(")
            {
                fprintf(stderr, "Annotation %s without parameters\n", Tokens[Index].c_str());
                return false;
            }

            /* Check if the size is in bytes */
            if (Tokens[Index].substr(12, 6) == "bytes_")
            {
                Annotation.ByteSize = true;
            }

            indexP1 = Index + 2;

            /* Check if the first parameter is dereferenced */
            if (Tokens[indexP1] == "*")
            {
                Annotation.DerefPreSizeParameter = true;
                indexP1++;
            }

            Annotation.PreSizeParameter = Tokens[indexP1];
            indexEnd = indexP1 + 1;

            /* Check whether this is the 2-parameter *_to_ version */
            if (Tokens[Index].substr(Tokens[Index].size() - 3, 3) == "to_")
            {
                indexP2 = indexP1 + 2;

                /* Check whether we have a ',' */
                if (Tokens[indexP1 + 1] != ",")
                {
                    fprintf(stderr, "Expected ',' got '%s'\n",
                            Tokens[indexP1 + 1].c_str());
                    return false;
                }

                /* Check if the first parameter is dereferenced */
                if (Tokens[indexP2] == "*")
                {
                    Annotation.DerefPostSizeParameter = true;
                    indexP2++;
                }

                Annotation.PostSizeParameter = Tokens[indexP2];
                indexEnd = indexP2 + 1;
            }

            /* Validate closing ')' */
            if (Tokens[indexEnd] != ")")
            {
                fprintf(stderr, "Expected ')' got '%s'\n",
                        Tokens[indexEnd].c_str());
                return false;
            }
        }
    }
    else if (Tokens[Index].substr(0, 7) == "_Inout_")
    {
        Annotation.Direction = Dir_Inout_;

        /* Check for the _updates_ variant */
        if (Tokens[Index].substr(5, 7) == "updates_")
        {
            /* These require 1 or 2 parameters */
            if (Tokens[Index + 1] != "(")
            {
                fprintf(stderr, "Annotation %s without parameters\n", Tokens[Index].c_str());
                return false;
            }

            /* Check if the size is in bytes */
            if (Tokens[Index].substr(12, 6) == "bytes_")
            {
                Annotation.ByteSize = true;
            }

            indexP1 = Index + 2;

            /* Check if the first parameter is dereferenced */
            if (Tokens[indexP1] == "*")
            {
                Annotation.DerefPreSizeParameter = true;
                indexP1++;
            }

            Annotation.PreSizeParameter = Tokens[indexP1];
            indexEnd = indexP1 + 1;

            /* Check whether this is the 2-parameter *_to_ version */
            if (Tokens[Index].substr(Tokens[Index].size() - 3, 3) == "to_")
            {
                indexP2 = indexP1 + 2;

                /* Check whether we have a ',' */
                if (Tokens[indexP1 + 1] != ",")
                {
                    fprintf(stderr, "Expected ',' got '%s'\n",
                            Tokens[indexP1 + 1].c_str());
                    return false;
                }

                /* Check if the first parameter is dereferenced */
                if (Tokens[indexP2] == "*")
                {
                    Annotation.DerefPostSizeParameter = true;
                    indexP2++;
                }

                Annotation.PostSizeParameter = Tokens[indexP2];
                indexEnd = indexP2 + 1;
            }

            /* Validate closing ')' */
            if (Tokens[indexEnd] != ")")
            {
                fprintf(stderr, "Expected ')' got '%s'\n",
                        Tokens[indexEnd].c_str());
                return false;
            }
        }
    }
    else
    {
        fprintf(stderr, "Unknown annotaton!\n");
        return false;
    }

    Index = indexEnd + 1;
    return true;
}

bool
ParseParameter(string& FunctionName, vector<string>& Tokens, int& Index, PARAMETER& Parameter)
{
    Parameter.Annotation.Direction = Dir_Unknown_;

    TracePrint("Checking parameter: '%s', '%s', '%s'\n", Tokens[Index].c_str(), Tokens[Index+1].c_str(), Tokens[Index+2].c_str());

    fprintf(stderr, "Check annotation: %s\n", Tokens[Index].c_str());
    // Check up to 5 annotations
    for (int i = 0; i < 5; i++)
    {
        string& anno = Tokens[Index];

        // If it doesn't look like an annotation, stop here
        if ((anno[0] != '_') ||
            (anno.back() != '_'))
        {
            break;
        }

        // Get the direction, if we have none yet
        ANNOTATION annotation;
        if (ParseAnnotation(FunctionName, Tokens, Index, annotation))
        {
            Parameter.Annotation = annotation;
        }
    }

    if (Parameter.Annotation.Direction == Dir_Unknown_)
    {
        fprintf(stderr, "unction '%s': Failed to get direction\n",
                FunctionName.c_str());
        return false;
    }

    fprintf(stderr, "Check type: %s\n", Tokens[Index].c_str());

    // Type should be all upper case
    Parameter.Type = Tokens[Index];
    for (int i = 0; i < Parameter.Type.size(); i++)
    {
        if (!isalpha(Parameter.Type[i]) || !isupper(Parameter.Type[i]))
        {
            fprintf(stderr, "Function '%s':Parameter type %s is not all uppercase\n",
                    FunctionName.c_str(),
                    Parameter.Type.c_str());
            return false;
        }
    }
    Index++;

    fprintf(stderr, "Check name: %s\n", Tokens[Index].c_str());

    // Now the Name should be all letters and start with
    Parameter.Name = Tokens[Index];
    for (int i = 0; i < Parameter.Name.size(); i++)
    {
        if (!isalnum(Parameter.Name[i]))
        {
            fprintf(stderr, "Function '%s':Parameter name %s has invalid characters\n",
                    FunctionName.c_str(),
                    Parameter.Name.c_str());
            return false;
        }
    }

    if (!isalpha( Parameter.Name[0]) || !isupper( Parameter.Name[0]))
    {
        fprintf(stderr, "Function '%s':Parameter name %s Does not start with uppercase letter\n",
                FunctionName.c_str(),
                Parameter.Name.c_str());
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

        if (!ParseParameter(Function.Name, Tokens, Index, parameter))
        {
            fprintf(stderr, "  Failed to parse parameters for %s.\n", Function.Name.c_str());
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
                    GetDirectionString(param.Annotation.Direction),
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
