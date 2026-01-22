// Token.hpp
#pragma once
#include <cstddef>

// type safe enum
enum class TokenType
{
	NULL_TOKEN,
	EON, // used to skip to sybol reading from readNumber: END OF NUMBER
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
	std::size_t startIndex;
	std::size_t length;
};
