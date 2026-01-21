// Token.hpp
#pragma once

// type safe enum
#include <cstddef>
typedef enum class TokenType
{
	NUMBER,
	PLUS,
	MINUS,
	MUL,
	DIV,
	LPAREN,
	RPAREN,
	EOF_TOKEN,
	ERROR
} TokenType;

typedef struct
{
	TokenType type;
	std::size_t startIndex;
	std::size_t length;
} Token;
