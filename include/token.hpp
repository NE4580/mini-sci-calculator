// Token.hpp
#pragma once
#include <cstddef>
#include <string>

// type safe enum
enum class TokenType
{
	NUMBER,
	PLUS,
	MINUS,
	MUL,
	DIV,
	PWR,
	FACTORIAL,
	FUNCTION,
	LPAREN,
	RPAREN,
	ERROR,
};

struct Token
{
	TokenType type;
	bool isFloat;
	size_t position;
	double value;
	std::string fname;
};
