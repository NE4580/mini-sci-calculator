#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include <iostream>

using namespace std;
int main(int argc, char** argv)
{

	string input("3!!");
	Lexer lexer(input);
	lexer.createTokens();
	lexer.translateImplicitMul();

	Parser p(lexer.getTokens());

	cout << p.evalute();
	// lexer.showTokens();
	return 0;
}
