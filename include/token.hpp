// Token.hpp
#pragma once
#include <cstddef>

// type safe enum
enum class TokenType
{
	NUMBER,
	PLUS,
	MINUS,
	MUL,
	DIV,
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
};
