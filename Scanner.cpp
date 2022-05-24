#include "Scanner.h"

using namespace scan;

Scanner::Scanner(string str, MapList<char, CHAR_TYPE> table)
{
    accept(str);
    this->table = table;
}

void Scanner::accept(string s)
{
    source = s;
    cchar_ptr = 0;
    cchar = get_source_char();
}

string Scanner::lexeme_string()
{
    return lexeme;
}

MapList<char, CHAR_TYPE> Scanner::getTable()
{
    return this->table;
}

void Scanner::setTable(MapList<char, CHAR_TYPE> table)
{
    this->table = table;
}

SYNTAX::TYPE Scanner::next_token()
{
    skip_whitespace();

    // check first non-whitespace
    switch (table.get(cchar))
    {
    case CHAR_TYPE::LETTER:
        get_word_token();
        break;

    case CHAR_TYPE::SPECIAL:
        get_special_token();
        break;

    case CHAR_TYPE::DIGIT:
        get_digit_token();
        break;

    //String Delimiter
    case CHAR_TYPE::STRING_DELIM:
        get_string_token();
        break;

    case CHAR_TYPE::EOF_TYPE:
        get_eof_token();
        break;
    
    default: //Error
        get_error_token();
        break;
    }
    return token;
}

void Scanner::skip_whitespace()
{
    while (table.get(cchar) == CHAR_TYPE::WHITESPACE)
        cchar = get_source_char();
}

char Scanner::get_source_char()
{
    char c;
    if (cchar_ptr + 1 <= source.size())
        c = source.at(cchar_ptr++);
    else
        c = Scanner::EOF_CHAR;

    return c;
}

void Scanner::get_word_token()
{
    lexeme = cchar;
    for (;;)
    {
        cchar = get_source_char();
        if (table.get(cchar) == CHAR_TYPE::LETTER)
            lexeme += cchar;
        else
            break;
    }
    token = SYNTAX::WORD_TOKEN;
}

void Scanner::get_eof_token()
{
    lexeme = "";
    token = SYNTAX::EOF_TOKEN;
}

void Scanner::get_special_token()
{
    lexeme = cchar;
    token = SYNTAX::SPECIAL_TOKEN;
    cchar = get_source_char();
}

unsigned long Scanner::get_position(){
    return cchar_ptr - 1;
}

void Scanner::get_digit_token()
{
    lexeme = cchar;
    for (;;)
    {
        cchar = get_source_char();
        if (table.get(cchar) == CHAR_TYPE::DIGIT)
            lexeme += cchar;
        else
            break;
    }
    token = SYNTAX::NUMBER_TOKEN;
}

void Scanner::get_string_token() 
{
    lexeme = "";
    for (;;)
    {
        cchar = get_source_char();
        if (table.get(cchar) == CHAR_TYPE::STRING_DELIM)
            break;

        lexeme += cchar;
    }

    cchar = get_source_char(); //move to next char
    token = SYNTAX::STRING_TOKEN;
}


void Scanner::get_error_token()
{
    lexeme = "";
    for (;;)
    {
        cchar = get_source_char();
        if (table.get(cchar) != CHAR_TYPE::ERROR)
            break;

        lexeme += cchar;
    }
    token = SYNTAX::BAD_TOKEN;
}

string Scanner::token_string()
{
    const char* msg[] = { 
        "ERROR", 
        "WORD",
        "NUMBER", 
        "SPECIAL",
        "WORD_STRING",
        "EOF" 
    };

    string s = msg[(int)token];
    return s;
}
