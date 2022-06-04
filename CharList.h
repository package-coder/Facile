#pragma once
#include "MapList.h"
#include "Scanner.h"

using namespace scan;

class CharList : public MapList<char, scan::CHAR_TYPE> {

public:

	static const int ALL_CHARS = 256;

	CharList() {
		for (int i = 0; i < CharList::ALL_CHARS; i++)
				put((char)i, CHAR_TYPE::ERROR);

		for (char i = 'A'; i <= 'Z'; i++)
			put(i, CHAR_TYPE::LETTER);

		for (char i = 'a'; i <= 'z'; i++)
			put(i, CHAR_TYPE::LETTER);

		for (char i = '0'; i <= '9'; i++)
			put(i, CHAR_TYPE::DIGIT);

		put({
			{'\r',		CHAR_TYPE::WHITESPACE},
			{'\n',		CHAR_TYPE::WHITESPACE},
			{'\t',		CHAR_TYPE::WHITESPACE},
			{' ',		CHAR_TYPE::WHITESPACE},
			{'{',		CHAR_TYPE::SPECIAL},
			{'}',		CHAR_TYPE::SPECIAL},
            {'(',		CHAR_TYPE::SPECIAL},
            {')',		CHAR_TYPE::SPECIAL},
            {';',		CHAR_TYPE::SPECIAL},
			{'$',		CHAR_TYPE::STRING_DELIM},
			{Scanner::EOF_CHAR, CHAR_TYPE::EOF_TYPE}
		});
	}

};