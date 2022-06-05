//
// Created by CHRIS on 5/9/2022.
//

#ifndef FACILE_SYNTAXTYPE_H
#define FACILE_SYNTAXTYPE_H

#include <iostream>


class SYNTAX{

public:
    enum TYPE {

        //Keywords
        VARIABLE_KEYWORD,
        CODE_KEYWORD,
        IN_KEYWORD,
        INT_KEYWORD,
        BLN_KEYWORD,
        STG_KEYWORD,
        ADD_KEYWORD,
        MUL_KEYWORD,
        SUB_KEYWORD,
        DIV_KEYWORD,
        MOD_KEYWORD,
        GRT_KEYWORD,
        GRE_KEYWORD,
        LET_KEYWORD,
        LEE_KEYWORD,
        EQL_KEYWORD,
        AND_KEYWORD,
        OHR_KEYWORD,
        NON_KEYWORD,
        PRT_KEYWORD,
        ASK_KEYWORD,
        PUT_KEYWORD,
        TRUE_KEYWORD,
        FALSE_KEYWORD,

        //Tokens
        BAD_TOKEN,
        NUMBER_TOKEN,
        WORD_TOKEN,
        SPECIAL_TOKEN,
        STRING_TOKEN,
        PLUS_TOKEN,
        MINUS_TOKEN,
        EOF_TOKEN,
        IDENTIFIER_TOKEN,
        OPEN_BRACE_TOKEN,
        CLOSE_BRACE_TOKEN,
        OPEN_PARENTHESIS_TOKEN,
        CLOSE_PARENTHESIS_TOKEN,
        SEMICOLON_TOKEN,
        DOLLAR_TOKEN,

        //Statements
        VARIABLE_STATEMENT,
        CODE_STATEMENT,
        MULTIPLE_DECLARATION_STATEMENT,
        DECLARATION_STATEMENT,
        PRINT_STATEMENT,
        PUT_STATEMENT,
        ASK_STATEMENT,

        //Expressions
        BINARY_EXPRESSION,
        PARENTHESIZED_EXPRESSION,
        NUMBER_EXPRESSION,
        LITERAL_EXPRESSION,
        IDENTIFIER_EXPRESSION,
        UNARY_EXPRESSION
    };

    static std::string toString(SYNTAX::TYPE type){
        const std::string str[] = {
            "VARIABLE_KEYWORD",
            "CODE_KEYWORD",
            "IN_KEYWORD",
            "INT_KEYWORD",
            "BLN_KEYWORD",
            "STG_KEYWORD",
            "ADD_KEYWORD",
            "MUL_KEYWORD",
            "SUB_KEYWORD",
            "DIV_KEYWORD",
            "MOD_KEYWORD",
            "GRT_KEYWORD",
            "GRE_KEYWORD",
            "LET_KEYWORD",
            "LEE_KEYWORD",
            "EQL_KEYWORD",
            "AND_KEYWORD",
            "OHR_KEYWORD",
            "NON_KEYWORD",
            "PRT_KEYWORD",
            "ASK_KEYWORD",
            "PUT_KEYWORD",
            "TRUE_KEYWORD",
            "FALSE_KEYWORD",
            "BAD_TOKEN",
            "NUMBER_TOKEN",
            "WORD_TOKEN",
            "SPECIAL_TOKEN",
            "STRING_TOKEN",
            "PLUS_TOKEN",
            "MINUS_TOKEN",
            "EOF_TOKEN",
            "IDENTIFIER_TOKEN",
            "OPEN_BRACE_TOKEN",
            "CLOSE_BRACE_TOKEN",
            "OPEN_PARENTHESIS_TOKEN",
            "CLOSE_PARENTHESIS_TOKEN",
            "SEMICOLON_TOKEN",
            "DOLLAR_TOKEN",
            "VARIABLE_STATEMENT",
            "CODE_STATEMENT",
            "MULTIPLE_DECLARATION_STATEMENT",
            "DECLARATION_STATEMENT",
            "PRINT_STATEMENT",
            "PUT_STATEMENT",
            "ASK_STATEMENT",
            "BINARY_EXPRESSION",
            "PARENTHESIZED_EXPRESSION",
            "NUMBER_EXPRESSION",
            "LITERAL_EXPRESSION",
            "IDENTIFIER_EXPRESSION",
            "UNARY_EXPRESSION"
        };

        return str[(unsigned long)type];
    }

};



#endif //FACILE_SYNTAXTYPE_H
