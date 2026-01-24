// Lexer.hpp

#pragma once
#include "token.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
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
	Token tokenizeSymbol(const char val, size_t beg);
	std::optional<Token> readNumber();
	std::optional<Token> readSymbol();
	void createTokens();
	void showTokens() const;
};
