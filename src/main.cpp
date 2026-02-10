#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string input("sin4");
	Lexer lexer(input);
	lexer.createTokens();
	lexer.translateImplicitMul();
	Parser parser(lexer.getTokens());

	lexer.showTokens();
	std::cout << "ANS: " << parser.evalute() << std::endl;
	return 0;
}
