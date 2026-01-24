#include "../include/lexer.hpp"

using namespace std;
int main(int argc, char** argv)
{
	string input("1+2.0");
	Lexer lexer(input);

	lexer.createTokens();

	lexer.showTokens();
	return 0;
}
