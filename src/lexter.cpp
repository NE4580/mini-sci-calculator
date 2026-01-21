#include "../include/lexter.hpp"

Lexer::Lexer(const std::string& text) : input(text) {}

Lexer::~Lexer() {}

const std::vector<Token>& Lexer::getTokens() const
{
	return std::vector<Token>();
}

void Lexer::readDigit() {}

void Lexer::readOPerator() {}

void Lexer::readParenthesis() {}

void Lexer::tokenize() {}
