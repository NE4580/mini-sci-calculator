#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include <iostream>

using namespace std;
int main(int argc, char** argv)
{

	string input("1*1+2-5/(10+4)");
	Lexer lexer(input);
	lexer.createTokens();
	Parser p(lexer.getTokens());

	double result = p.evalute();
	std::cout << result << std::endl;
	return 0;
}
