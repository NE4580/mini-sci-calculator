#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include <iostream>
#include <optional>

using namespace std;
int main(int argc, char** argv)
{
	string input("-(2+(12/4*2))");
	Lexer lexer(input);
	lexer.createTokens();
	Parser p(lexer.getTokens());

	double result = p.evalute();
	std::cout << result;
	return 0;
}
