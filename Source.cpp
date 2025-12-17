#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <regex>
#include <vector>
#include <stack>
#include <fstream>
#include "Grammer.h"
using namespace std;


int main()
{
	string text = "";
	ifstream file;
	file.open("code.txt");
	string x;
	while (file >> x) {
		text += x + " ";
	}
	text += "$";
	
	Grammer *grammer = new Grammer(text);

	grammer->compile();
	

	return 0;
}
