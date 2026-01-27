#include "../include/parser.hpp"
#include <cstdio>
#include <cstdlib>
#include <optional>

Parser::Parser(const std::vector<Token>& t) : tokens(t) { tokenIndex = 0; }

double Parser::evalute()
{
	double result = 0;

	if (tokens.size() > 0)
	{
		auto value = expression();
		if (!value)
		{
			puts("PARSE ERROR\n");
			std::exit(1);
		}

		// ensure all tokens were consumed
		if (currentToken().has_value())
		{
			puts("UNEXPECTED TOKEN AFTER EXPRESSION\n");
			std::exit(1);
		}
		result = value->number;
	}

	return result;
}

std::optional<Token> Parser::peek()
{
	if (tokenIndex + 1 < tokens.size())
		return tokens[tokenIndex + 1];
	else
		return std::nullopt;
}

std::optional<Token> Parser::currentToken() const
{
	if (tokenIndex < tokens.size())
		return tokens[tokenIndex];
	else
		return std::nullopt;
}

void Parser::advance()
{
	if (tokenIndex < tokens.size()) { tokenIndex += 1; }
}

bool Parser::isClosingPren()
{
	if (!currentToken()) return false;

	if (!(currentToken()->type == TokenType::RPAREN)) return false;

	advance();
	return true;
}

bool Parser::match(TokenType tt)
{
	if (!currentToken()) return false;

	if (currentToken())
		return (currentToken()->type == tt) ? true : false;
	else
		return false;
}

std::optional<Value> Parser::expression()
{
	std::optional<Value> leftOprand = term();
	std::optional<Value> rightOprand;

	if (!leftOprand) return std::nullopt;

	while (match(TokenType::PLUS) ||
	       match(TokenType::MINUS)) // if operator is a match
	{
		TokenType op = currentToken()->type; // Coleect token type directly
		advance();                           // consume operator

		rightOprand = term();

		if (!rightOprand) // break out if no oprand
			break;

		if (op == TokenType::PLUS)
			leftOprand->number = leftOprand->number + rightOprand->number;

		else if (op == TokenType::MINUS)
			leftOprand->number = leftOprand->number - rightOprand->number;

		leftOprand->isFloat = leftOprand->isFloat || rightOprand->isFloat;
	}

	return leftOprand;
}

std::optional<Value> Parser::term()
{
	std::optional<Value> leftOprand = factor();
	std::optional<Value> rightOprand;

	if (!leftOprand) return std::nullopt;

	while (
	    match(TokenType::MUL) ||
	    match(TokenType::DIV)) // if operator is a match, move past the operator
	{
		TokenType op = currentToken()->type; // Coleect token type directly
		advance();                           // consume operator

		rightOprand = factor();

		if (!rightOprand) // break out if no oprand
			break;

		if (op == TokenType::MUL)
			leftOprand->number = leftOprand->number * rightOprand->number;

		else if (op == TokenType::DIV)
			leftOprand->number = leftOprand->number / rightOprand->number;

		leftOprand->isFloat = leftOprand->isFloat || rightOprand->isFloat;
	}

	return leftOprand;
}

std::optional<Value> Parser::factor()
{
	short unaryPoM = -1;
	std::optional<Value> number;

	if (!currentToken()) return std::nullopt;

	if (currentToken()->type == TokenType::PLUS)
	{
		unaryPoM = 0; // 0 to mark neutral effect of plus when unary
		advance();
		number = factor();
	}
	else if (currentToken()->type == TokenType::MINUS)
	{
		unaryPoM = 1;
		advance();
		number = factor();
	}
	else if (currentToken()->type == TokenType::NUMBER)
	{
		number = Value{currentToken()->value, currentToken()->isFloat};
		advance();
	}
	else if (currentToken()->type == TokenType::LPAREN)
	{
		advance();
		number = expression();
		if (!isClosingPren()) // expecting ) at the end of call to
		                      // expression()
			return std::nullopt;
	}
	else
		return std::nullopt;

	if (unaryPoM == 1) number->number *= -1; // negate when minus is unary

	return number;
}
