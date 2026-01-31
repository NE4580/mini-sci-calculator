#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string input("(2)(2)");
	Lexer lexer(input);
	lexer.createTokens();
	lexer.translateImplicitMul();
	Parser parser(lexer.getTokens());

	std::cout << "ANS: " << parser.evalute() << std::endl;
	// lexer.showTokens();
	return 0;
}
