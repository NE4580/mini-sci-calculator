#include "../include/lexter.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

Lexer::Lexer(const std::string& text) : input(text) { position = 0; }

bool Lexer::isSymbol() const
{
	if ((input[position] == '+') || (input[position] == '-') ||
	    (input[position] == '/') || (input[position] == '*') ||
	    (input[position] == '(') || (input[position] == ')'))
		return true;
	else
		return false;
}

void Lexer::showTokens() const
{
	std::cout << "Tokens: " << tokens.size() << std::endl;
	for (const auto& token : tokens)
		std::cout << "Index: " << token.startIndex << " LEN: " << token.length
		          << std::endl;
}

Token Lexer::readNumber()
{
	size_t next = position + 1, startI = position;
	size_t appendIndex = 0;
	std::string value  = "";
	bool makeToken     = false;

	while (true)
	{
		if (position < input.size()) // if position is in bounds
		{
			if (input[position] == ' ') position++;

			if (input[position] == '.' && input[next] == '.')
			{
				std::cerr
				    << "ERROR: Unexpected duo decimal point \'.\' at position of input"
				    << position << std::endl;
				return Token{TokenType::ERROR, position, 1};
			}

			else if (std::isdigit(input[position]) || input[position] == '.')
			{
				value.insert(appendIndex++, 1,
				             input[position]); // make a string of the whole number
				position += (position < input.size()) ? 1 : 0;
				next += (position < input.size()) ? 1 : 0;
				makeToken = true;
			}

			else if (isSymbol())
			{
				if (makeToken)
					break;
				else
					return Token{TokenType::EON, position, 1};
			}
		} // end of bound check

		else // break if out of bounds
			break;
	}

	return tokenize(value, startI);
}

Token Lexer::readSymbols()
{
	std::string value = "";
	int startI        = position;

	if (input[position] == ' ') position++;

	if (isSymbol())
	{
		value = input[position];
		position += (position < input.size()) ? 1 : 0;
	}

	return tokenize(value, startI);
}

Token Lexer::tokenize(const std::string& val, size_t beg)
{
	TokenType tokenType = TokenType::NULL_TOKEN;

	if (std::isdigit(val[0]))
		tokenType = TokenType::NUMBER;

	else if (val[0] == '+')
		tokenType = TokenType::PLUS;

	else if (val[0] == '-')
		tokenType = TokenType::MINUS;

	else if (val[0] == '*')
		tokenType = TokenType::MUL;

	else if (val[0] == '/')
		tokenType = TokenType::DIV;

	else if (val[0] == '(')
		tokenType = TokenType::LPAREN;

	else if (val[0] == ')')
		tokenType = TokenType::RPAREN;

	return Token{tokenType, beg, val.size()};
}

static bool validToken(Token& token)
{
	bool isValid = true;
	if (token.type == TokenType::ERROR || token.type == TokenType::NULL_TOKEN)
		isValid = false;

	return isValid;
}

void Lexer::createTokens()
{
	while (position < input.size())
	{
		Token token = readNumber();
		if (!(token.type == TokenType::EON))
			if (validToken(token)) tokens.push_back(token);

		token = readSymbols();
		if (validToken(token)) tokens.push_back(token);
	}
}
