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
	PWR,
	FACTORIAL,
	SIN,
	COS,
	TAN,
	ASIN,
	ACOS,
	ATAN,
	SQUREROOT,
	CUBEROOT,
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
