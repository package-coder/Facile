#pragma once

#include <iostream>
#include "MapList.h"
#include "SyntaxType.h"

using namespace std;

namespace scan {
    enum class CHAR_TYPE
    {
        WHITESPACE,
        LETTER,
        DIGIT,
        SPECIAL,
        STRING_DELIM,
        ERROR,
        EOF_TYPE
    };

    enum class TOKEN_CODE
    {
        ERROR,
        WORD,
        NUMBER,
        SPECIAL,
        STRING,
        EOF_TOKEN
    };


    class Scanner
    {
    public:
        static const char EOF_CHAR = 127;


        // constructors
        Scanner(string, MapList<char, CHAR_TYPE>);

        // public member functions
        void accept(string);
        SYNTAX::TYPE next_token();
        string token_string();
        string lexeme_string();
        unsigned long get_position();
        MapList<char, CHAR_TYPE> getTable();
        void setTable(MapList<char, CHAR_TYPE>);

    private:
        MapList<char, CHAR_TYPE> table;
        string source;

        string lexeme;
        SYNTAX::TYPE token;

        unsigned long cchar_ptr;
        char cchar;

        // private member functions
        void skip_whitespace();
        char get_source_char();
        void get_word_token();
        void get_special_token();
        void get_digit_token();
        void get_string_token();
        void get_error_token();
        void get_eof_token();
    };
}