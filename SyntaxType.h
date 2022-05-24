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

        //Tokens
        BAD_TOKEN,
        NUMBER_TOKEN,
        WORD_TOKEN,
        SPECIAL_TOKEN,
        STRING_TOKEN,
        PLUS_TOKEN,
        MINUS_TOKEN,
        EOF_TOKEN,
        DATATYPE_TOKEN,
        IDENTIFIER_TOKEN,
        OPEN_BRACE_TOKEN,
        CLOSE_BRACE_TOKEN,
        OPEN_PARENTHESIS_TOKEN,
        CLOSE_PARENTHESIS_TOKEN,
        SEMICOLON_TOKEN,
        DOLLAR_TOKEN,

        //Blocks
        VARIABLE_BLOCK,
        CODE_BLOCK,

        //Statements
        MULTIPLE_VARIABLE_DECLARATION,
        VARIABLE_DECLARATION,
        PRINT_STATEMENT,

        //Expressions
        NUMBER_EXPRESSION,
        STRING_LITERAL_EXPRESSION
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
            "BAD_TOKEN",
            "NUMBER_TOKEN",
            "WORD_TOKEN",
            "SPECIAL_TOKEN",
            "STRING_TOKEN",
            "PLUS_TOKEN",
            "MINUS_TOKEN",
            "EOF_TOKEN",
            "DATATYPE_TOKEN",
            "IDENTIFIER_TOKEN",
            "OPEN_BRACE_TOKEN",
            "CLOSE_BRACE_TOKEN",
            "OPEN_PARENTHESIS_TOKEN",
            "CLOSE_PARENTHESIS_TOKEN",
            "SEMICOLON_TOKEN",
            "DOLLAR_TOKEN",
            "VARIABLE_BLOCK",
            "CODE_BLOCK",
            "MULTIPLE_VARIABLE_DECLARATION",
            "VARIABLE_DECLARATION",
            "PRINT_STATEMENT",
            "NUMBER_EXPRESSION",
            "STRING_LITERAL_EXPRESSION",
        };

        return str[(unsigned long)type];
    }

};



#endif //FACILE_SYNTAXTYPE_H
