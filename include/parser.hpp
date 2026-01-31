// Parser

#pragma once
#include "token.hpp"
#include <optional>
#include <string>
#include <vector>

struct Value
{
	double number;
	bool isFloat;
};

class Parser
{
private:
	size_t tokenIndex;
	std::vector<Token> tokens;

public:
	explicit Parser(const std::vector<Token>& t);
	double evalute();

private:
	std::optional<Token> peek();
	std::optional<Token> currentToken() const;
	void advance();
	bool match(TokenType tt);
	bool isOpeningPren();
	bool isClosingPren();
	bool isFunction(TokenType tt) const;
	double toRadians(double angle);
	double fromRadians(double angle);
	std::optional<Value> expression();
	std::optional<Value> term();
	std::optional<Value> unary();
	std::optional<Value> power();
	std::optional<Value> postfix();
	std::optional<Value> factor();
	std::optional<Value> function(std::string tt, double x);
};
