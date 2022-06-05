#include "MapList.h"
#include "SyntaxType.h"
#include <string>

class SyntaxList : public MapList<std::string, SYNTAX::TYPE>{
public:
    SyntaxList(){
        put({
            {"variable",	SYNTAX::VARIABLE_KEYWORD},
            {"code",		SYNTAX::CODE_KEYWORD},
            {"PRT",			SYNTAX::PRT_KEYWORD},
            {"ASK",			SYNTAX::ASK_KEYWORD},
            {"PUT",			SYNTAX::PUT_KEYWORD},
            {"IN",			SYNTAX::IN_KEYWORD},
            {"INT",			SYNTAX::INT_KEYWORD},
            {"BLN",			SYNTAX::BLN_KEYWORD},
            {"STG",			SYNTAX::STG_KEYWORD},
            {"ADD",			SYNTAX::ADD_KEYWORD},
            {"MUL",			SYNTAX::MUL_KEYWORD},
            {"SUB",			SYNTAX::SUB_KEYWORD},
            {"DIV",			SYNTAX::DIV_KEYWORD},
            {"MOD",			SYNTAX::MOD_KEYWORD},
            {"GRT",			SYNTAX::GRT_KEYWORD},
            {"GRE",			SYNTAX::GRE_KEYWORD},
            {"LET",			SYNTAX::LET_KEYWORD},
            {"LEE",			SYNTAX::LEE_KEYWORD},
            {"EQL",			SYNTAX::EQL_KEYWORD},
            {"AND",			SYNTAX::AND_KEYWORD},
            {"OHR",			SYNTAX::OHR_KEYWORD},
            {"NON",			SYNTAX::NON_KEYWORD},
            {"true",		SYNTAX::TRUE_KEYWORD},
            {"false",		SYNTAX::FALSE_KEYWORD},
            {"{",           SYNTAX::OPEN_BRACE_TOKEN},
            {"}",           SYNTAX::CLOSE_BRACE_TOKEN},
            {"(",           SYNTAX::OPEN_PARENTHESIS_TOKEN},
            {")",           SYNTAX::CLOSE_PARENTHESIS_TOKEN},
            {";",           SYNTAX::SEMICOLON_TOKEN},
            {"$",           SYNTAX::DOLLAR_TOKEN}
        });
    }
};