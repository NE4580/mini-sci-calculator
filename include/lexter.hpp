// Lexer.hpp

#pragma once
#include "token.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

class Lexer
{
private:
	const std::string& input;
	size_t position;
	std::vector<Token> tokens;

	bool isSymbol() const;

public:
	explicit Lexer(const std::string& text); // forbit inplicit conversions
	                                         // like Lexer t = "tf"
	Token tokenize(const std::string& val, size_t beg);
	Token readNumber();
	Token readSymbols();
	void createTokens();
	void showTokens() const;
};
