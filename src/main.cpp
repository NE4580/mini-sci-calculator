#include "../include/lexter.hpp"

using namespace std;
int main(int argc, char** argv)
{
	string input("11 * (1 + 1)");
	Lexer lexer(input);

	lexer.createTokens();

	lexer.showTokens();
	return 0;
}
