#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string input("sin90");
	Lexer lexer(input);
	lexer.createTokens();
	lexer.translateImplicitMul();
	Parser parser(lexer.getTokens());

	std::cout << "ANS: " << parser.evalute() << std::endl;
	// lexer.showTokens();
	return 0;
}
