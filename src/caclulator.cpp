#include "caclulator.hpp"
#include <iostream>
#include <vector>

Calculator::Calculator()
{
	lexer  = nullptr;
	parser = nullptr;
	input  = "";
	index  = 0;
}

Calculator::~Calculator()
{
	if (lexer) delete lexer;
	if (parser) delete parser;
}

void Calculator::getInput()
{
	std::string expression;
	std::cout << "Type Expression: ";
	std::cin >> expression;

	if (!validateInput(expression))
		std::cout << "SYNTAX ERROR" << std::endl;
	else
		std::cout << "PASS" << std::endl;
}
bool Calculator::validateInput(std::string expr) const { return true; }
bool Calculator::normalizeInput() { return true; }
void Calculator::showLexerInput() const {}
bool Calculator::evalute() { return true; }
void Calculator::dispalyResult() const {}
