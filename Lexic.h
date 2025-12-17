#pragma once
#include <string>

#define _ASSIGN "T_:="
#define _ASSIGN_REG "\\:="

#define _ADD "T_+"
#define _ADD_REG "\\+"

#define _MULTIPLE "T_*"
#define _MULTIPLE_REG "\\*"

#define O_Parenthes "T_("
#define O_Parenthes_REG "\\("

#define C_Parenthes "T_)"
#define C_Parenthes_REG "\\)"

#define _ID "T_ID"
#define _ID_REG "[_a-zA-Z][_a-zA-Z0-9]*"

#define _DOLLAR "T_$"
#define _DOLLAR_REG "\\$"

using namespace std;

class Token {
public:
	string name;
	string value;
	string regular;

	Token(string);
	Token(string, string);
	Token(string, string,string);
};


Token::Token(string name, string value) {
	this->name = name;
	this->value = value;
}

Token::Token(string name) {
	this->name = name;
	this->value = "";
}

Token::Token(string name, string value , string regular) {
	this->name = name;
	this->value = value;
	this->regular = regular;
}
