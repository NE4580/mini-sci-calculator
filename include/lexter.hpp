// Lexer.hpp

#pragma once
#include "token.hpp"
#include <iostream>
#include <vector>

class Lexer
{
private:
	const std::string& input;
	size_t position;
	std::vector<Token> tokens;

public:
	explicit Lexer(const std::string& text); // forbit inplicit conversions
	                                         // like Lexer t = "tf"
	void tokenize();
	void readDigit();
	void readOPerator();
	void readParenthesis();
	const std::vector<Token>& getTokens() const;
	~Lexer();
};
