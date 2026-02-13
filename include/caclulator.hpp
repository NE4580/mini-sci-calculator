#pragma once
#include "lexer.hpp"
#include "parser.hpp"

class Calculator
{
private:
	Lexer* lexer;
	Parser* parser;
	std::string input;
	size_t index;

public:
	Calculator();
	void getInput();
	bool validateInput(std::string expr) const;
	bool normalizeInput();
	void showLexerInput() const;
	bool evalute();
	void dispalyResult() const;
	~Calculator();
};
