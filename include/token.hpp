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
	IDENTIFIER,
	MOD,
	LPAREN,
	RPAREN,
	COMMA,
	ERROR,
	MODEXEP,
};

struct Token
{
	TokenType type;
	bool isFloat;
	size_t position;
	double value;
	std::string fname;
};
