#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Lexic.h"
#include <regex>
using namespace std;

class Address
{
public:
	string	Operator;
	string	Address_1;
	string  Address_2;
	string  Address_3;
	Address(string , string ,string , string);
};

Address::Address(string Operator, string Address_1, string Address_2, string Address_3)
{
	this->Operator = Operator;
	this->Address_1 = Address_1;
	this->Address_2 = Address_2;
	this->Address_3 = Address_3;
}

class Variable {
public:
	string name;
	float value;
	Variable(string , float);
};

Variable::Variable(string name, float value)
{
	this->name = name;
	this->value = value;
}


class Grammer
{
public:
	 Grammer(string text);
	 stack < string > semantic_stack;
	 vector<string> temp;
	 vector <Variable > variables;
	 int variables_index = 400;

	 vector <float > temp_variables;
	 int temp_variables_index = 600;

	 vector < Address > addresses;


	 vector <Token> tokens;
	 int token_index;

	 const vector<string> explode(const string& s, const char& c)
	 {
		 string buff{ "" };
		 vector<string> v;

		 for (auto n : s)
		 {
			 if (n != c) buff += n; else
				 if (n == c && buff != "") { v.push_back(buff); buff = ""; }
		 }
		 if (buff != "") v.push_back(buff);

		 return v;
	 }

	 void S() {
		 if (tokens[token_index].name == _ID) {
			 L();
			 check_token(_ASSIGN);
			 E();
			 action_assign();
		 }
		 else if (tokens[token_index].name == _DOLLAR) {}
		 else {
			 Error();
		 }
	 }

	 void E() {
		 if (tokens[token_index].name == O_Parenthes || tokens[token_index].name == _ID) {
			 T();
			 Eprime();
		 }
		 else if (tokens[token_index].name == _DOLLAR || tokens[token_index].name == C_Parenthes) {}
		 else {
			 Error();
		 }
	 }

	 void Eprime() {
		 if (tokens[token_index].name == _ADD) {
			 check_token(_ADD);
			 T();
			 action_pluse();
			 Eprime();
		 }
		 else if (tokens[token_index].name == _DOLLAR || tokens[token_index].name == C_Parenthes) {}
		 else {
			 Error();
		 }
	 }

	 void T() {
		 if (tokens[token_index].name == O_Parenthes || tokens[token_index].name == _ID) {
			 F();
			 Tprime();
		 }
		 else if (tokens[token_index].name == _ADD || tokens[token_index].name == C_Parenthes || tokens[token_index].name == _DOLLAR) {}
		 else {
			 Error();
		 }
	 }

	 void Tprime() {
		 if (tokens[token_index].name == _MULTIPLE) {
			 check_token(_MULTIPLE);
			 F();
			 action_multiple();
			 Tprime();
		 }
		 else if (tokens[token_index].name == _ADD || tokens[token_index].name == C_Parenthes || tokens[token_index].name == _DOLLAR) {}
		 else {
			 Error();
		 }
	 }


	 void F() {
		 if (tokens[token_index].name == O_Parenthes) {
			 check_token(O_Parenthes);
			 E();
			 check_token(C_Parenthes);
		 }
		 else if (tokens[token_index].name == _ID) {
			 action_pid();
			 check_token(_ID);
		 }
		 else if (tokens[token_index].name == _ADD || tokens[token_index].name == _MULTIPLE || tokens[token_index].name == C_Parenthes || tokens[token_index].name == _DOLLAR) {}
		 else {
			 Error();
		 }
	 }

	 void L() {
		 if (tokens[token_index].name == _ID) {
			 action_pid();
			 check_token(_ID);
		 }
		 else if (tokens[token_index].name == _ASSIGN) {}
		 else {
			 Error();
		 }
	 }
	 void action_pid() {
		 string index = findAddress(tokens[token_index].value);
		 semantic_stack.push(index);
	 }

	 void action_multiple() {
		 string top = semantic_stack.top();
		 semantic_stack.pop();
		 string top_p = semantic_stack.top();
		 semantic_stack.pop();

		 
		 float temp = 0.0;
		 temp_variables.push_back(temp);
		 int t = temp_variables.size() - 1 + temp_variables_index;
		 semantic_stack.push(to_string(t));

		 Address obj("*", top_p , top, to_string(t));
		 addresses.push_back(obj);
	 }

	 void action_pluse() {
		 string top = semantic_stack.top();
		 semantic_stack.pop();
		 string top_p = semantic_stack.top();
		 semantic_stack.pop();


		 float temp = 0.0;
		 temp_variables.push_back(temp);
		 int t = temp_variables.size() - 1 + temp_variables_index;
		 semantic_stack.push(to_string(t));

		 Address obj("+", top_p, top,to_string(t));
		 addresses.push_back(obj);
	 }


	 void action_assign() {
		 string  top = semantic_stack.top();
		 semantic_stack.pop();

		 string top_p = semantic_stack.top();
		 semantic_stack.pop();

		 Address obj("=", top, "", top_p);
		 addresses.push_back(obj);
	 }

	 void check_token(string reg) {
		 if (tokens[token_index].name == reg) {
			 token_index++;
		 }
		 else {
			 Error();
		 }
	 }

	 void explode_tokens(string a)
	 {

		 string name ,value = "";
		 if (regex_match(a, regex(_ASSIGN_REG)))
		 {
			 name = _ASSIGN;	
		 }
		 else if (regex_match(a, regex(_ADD_REG)))
		 {
			 name = _ADD;
		 }
		 else if (regex_match(a, regex(_MULTIPLE_REG)))
		 {
			 name = _MULTIPLE;
		 }
		 else if (regex_match(a, regex(O_Parenthes_REG)))
		 {
			 name = O_Parenthes;
		 }
		 else if (regex_match(a, regex(C_Parenthes_REG)))
		 {
			 name = C_Parenthes;
		 }
		 else if (regex_match(a, regex(_ID_REG)))
		 {
			 name = _ID;
			 value = a;
		 }
		 else if (regex_match(a, regex(_DOLLAR_REG)))
		 {
			 name = _DOLLAR;
			 value = a;
		 }
		 else if (regex_match(a, regex(".*")))
		 {
			 Error();
			 return;

		 }

		 Token token(name, value);
		 tokens.push_back(token);
	 }



	 void Error() {
		 exit(1);
	 }

	 string findAddress(string a) {
		 for (int i = 0; i < variables.size(); i++)
			 if (regex_match(variables[i].name, regex(a)))
				 return to_string(i);
		 Variable obj(a,0.0);
		 variables.push_back(obj);
		 return to_string(variables_index + (variables.size() - 1));
	 }

	 void print_code() {
		 for (int i = 0; i < addresses.size(); i++) {
			 cout << "(" << addresses[i].Operator << "," << addresses[i].Address_1 << "," << addresses[i].Address_2 << "," << addresses[i].Address_3 << ")\n";
		 }
	 }

	 void compile() {
		 S();
		 print_code();
	 }
};


 Grammer:: Grammer(string text)
{
	 tokens.empty();
	 this->temp = explode(text,' ');
	 for (int i = 0; i < temp.size(); i++) {
		 explode_tokens(temp[i]);
	 }
}
