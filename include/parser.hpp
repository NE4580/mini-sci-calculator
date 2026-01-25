// Parser

#pragma once
#include "token.hpp"
#include <optional>
#include <vector>

class Parser
{
private:
	size_t current;
	std::vector<Token> tokens;

public:
	explicit Parser(const std::vector<Token>& t);
	double evalute();
	std::optional<Token> peek();
	void advance();

private:
	double expression();
	double term();
	double factor();
};
