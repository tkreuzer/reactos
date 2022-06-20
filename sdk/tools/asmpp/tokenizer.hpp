
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <ctime>

#ifdef _MSC_VER
#define throw __debugbreak(); throw
#endif

extern time_t search_time;

struct TOKEN_DEF
{
    int Type;
    std::string RegExString;
};

class Token
{
    const std::string& m_text;
    unsigned int m_pos;
    unsigned int m_len;
#if _DEBUG
    std::string m_dbgstr;
#endif
    int m_type;

public:

    Token(const std::string& text, size_t pos, size_t len, int type)
        : m_text(text),
        m_pos(static_cast<unsigned int>(pos)),
        m_len(static_cast<unsigned int>(len)),
        m_type(type)
    {
#if _DEBUG
        m_dbgstr = str();
#endif
    }

    std::string str() const
    {
        return m_text.substr(m_pos, m_len);
    }

    int type() const
    {
        return m_type;
    }
};

struct Tokenizer
{
    const std::vector<TOKEN_DEF> &m_tokendefs;
    const std::regex m_re;

    typedef int myint;

    static
    unsigned int
    count_captures(const std::string& exp)
    {
        bool in_char_group = false;
        unsigned int count = 0;

        for (size_t i = 0; i < exp.size(); i++)
        {
            char c = exp[i];

            // Skip escaped characters
            if (c == '\\')
            {
                i++;
                continue;
            }

            if (in_char_group)
            {
                if (c == ']')
                {
                    in_char_group = false;
                }
                continue;
            }

            if (c == '[')
            {
                in_char_group = true;
                continue;
            }

            if (c == '(')
            {
                if (exp[i + 1] != '?')
                {
                    count++;
                }
            }
        }

        return count;
    }

    static
    std::regex
    CompileMultiRegex(const std::vector<TOKEN_DEF> &tokendefs)
    {
        std::string combinedString;

        if (tokendefs.size() == 0)
        {
            return std::regex();
        }

        // Validate all token definitions
        for (auto def : tokendefs)
        {
            size_t found = -1;

            // Count capture groups
            unsigned int count = count_captures(def.RegExString);
            if (count != 1)
            {
                throw "invalid count!\n";
            }
        }

        // Combine all expressions into one (one capture group for each)
        combinedString = "(?:" + tokendefs[0].RegExString + ")";
        for (size_t i = 1; i < tokendefs.size(); i++)
        {
            combinedString += "|(?:" + tokendefs[i].RegExString + ")";
        }

        return std::regex(combinedString, std::regex_constants::icase);
    }

public:

    struct TOKEN_REF
    {
        unsigned int pos;
        unsigned int len;
        int type;
    };

    Tokenizer(std::vector<TOKEN_DEF> &tokendefs)
        : m_tokendefs(tokendefs),
          m_re(CompileMultiRegex(tokendefs))
    {
    }

    TOKEN_REF match(std::smatch &matches, const std::string& str) const
    {
        return match(matches, str, 0);
    }

    TOKEN_REF match(std::smatch &matches, const std::string &str, size_t startpos) const
    {
        const std::string::const_iterator first = str.cbegin() + startpos;
        const std::string::const_iterator last = str.cend();

        // If we reached the end, there is nothing more to do
        if (first == last)
        {
            return TOKEN_REF{ static_cast<unsigned int>(startpos), 0, -1 };
        }

        time_t start_time = time(NULL);

        // Try to find a match
        if (!std::regex_search(first, last, matches, m_re))
        {
            throw "Failed to match\n";
        }

        search_time += time(NULL) - start_time;

        // Validate that it's at the start of the string
        if (matches.prefix().matched)
        {
            throw "Failed to match at current position!\n";
        }
        
        // We have a match, check which one it is
        for (size_t i = 1; i < matches.size(); i++)
        {
            if (matches[i].matched)
            {
                unsigned int len = static_cast<unsigned int>(matches.length(i));
                int type = m_tokendefs[i - 1].Type;
                return TOKEN_REF{ static_cast<unsigned int>(startpos), len, type};
            }
        }

        // We should never get here
        throw "Something went wrong!\n";
        //return Token();
    }
};

#if 0
class TokenList;

class TokenStream
{
    using TOKEN_REF = typename Tokenizer::TOKEN_REF;
    friend class TokenList;

    const Tokenizer &m_tokenizer;
    const std::string m_text;

public:

    class TokenIterator
    {
        friend class TokenStream;
        const class TokenStream& m_stream;
        TOKEN_REF m_tref;

        TokenIterator(const class TokenStream& tokstream)
            : m_stream(tokstream),
              m_tref(tokstream.m_tokenizer.match(tokstream.m_text, 0))
        {
        }

        TokenIterator(const class TokenStream& tokstream, size_t pos, size_t len)
            : m_stream(tokstream),
              m_tref{ static_cast<unsigned int>(pos), static_cast<unsigned int>(len), -1 }
        {
        }

    public:

        TokenIterator operator++()
        {
            // Nothing to do from last position
            if (m_tref.pos == m_stream.m_text.size())
            {
                return *this;
            }

            // Search for the next token
            m_tref = m_stream.m_tokenizer.match(m_stream.m_text, m_tref.pos + m_tref.len);

            return *this;
        }

        bool operator!=(TokenIterator &other)
        {
            return (m_tref.pos != other.m_tref.pos);
        }

        Token operator*()
        {
            std::string str = m_stream.m_text.substr(m_tref.pos, m_tref.len);
            return Token(str, m_tref.type);
        }

    };

    TokenStream(Tokenizer &tokenizer, std::string &text)
        : m_tokenizer(tokenizer),
          m_text(text)
    {
    }

#if 0
    TokenStream(Tokenizer &tokenizer, std::ifstream &file)
        : m_tokenizer(tokenizer)
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        m_text = buffer.str();
    }
#endif

    TokenIterator begin()
    {
        return TokenIterator(*this);
    }

    TokenIterator end()
    {
        return TokenIterator(*this, m_text.size(), 0);
    }

    TokenIterator cbegin() const
    {
        return TokenIterator(*this);
    }

    TokenIterator cend() const
    {
        return TokenIterator(*this, m_text.size(), 0);
    }

    Token match(size_t pos) const
    {
        TOKEN_REF tref = m_tokenizer.match(m_text, pos);
        std::string str = m_text.substr(tref.pos, tref.len);
        return Token(str, tref.type);
    }

};
#endif

class TokenList
{
    using TOKEN_REF = typename Tokenizer::TOKEN_REF;

    const Tokenizer& m_tokenizer;
    const std::string& m_text;
    std::vector<TOKEN_REF> m_tokens;

public:

    TokenList(const Tokenizer& tokenizer, const std::string& text)
        : m_tokenizer(tokenizer),
          m_text(text)
    {
        size_t startpos = 0;
        size_t len = m_text.size();
        std::smatch matches;

        m_tokens.reserve(len / 5);

        while (startpos < len)
        {
            TOKEN_REF tref = m_tokenizer.match(matches, m_text, startpos);
            m_tokens.push_back(tref);
            startpos += tref.len;
        };
    }

    size_t size() const
    {
        return m_tokens.size();
    }

    Token operator[](size_t n) const
    {
        return Token(m_text, m_tokens[n].pos, m_tokens[n].len, m_tokens[n].type);
    }

};
