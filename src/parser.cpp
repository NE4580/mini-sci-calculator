#include "../include/parser.hpp"
#include <optional>

Parser::Parser(const std::vector<Token>& t) : tokens(t) { current = 0; }

double Parser::evalute()
{
	double result = 0;

	if (tokens.size() > 0) result = expression();
}

std::optional<Token> Parser::peek()
{
	if (current + 1 < tokens.size())
		return tokens[current + 1];
	else
		return std::nullopt;
}

void Parser::advance() { current += (current < tokens.size()) ? 1 : 0; }

double Parser::expression()
{
	double leftOprand = term();
	double rightOprand;
	size_t nextTokenIndex = (current + 1 < tokens.size()) ? current + 1 : 0;
	if (peek())
	{
		if (tokens[nextTokenIndex].type == TokenType::PLUS)
		{
			advance(); // move to operator
			advance(); // move to possible next Oprand
			rightOprand = term();
			leftOprand  = leftOprand + rightOprand;
		}
		else if (tokens[nextTokenIndex].type == TokenType::MINUS)
		{
			advance(); // move to operator
			advance(); // move to possible next Oprand
			rightOprand = factor();
			leftOprand  = leftOprand - rightOprand;
		}
	}

	return leftOprand;
}

double Parser::term()
{
	double leftOprand = factor();
	double rightOprand;
	size_t nextTokenIndex = (current + 1 < tokens.size()) ? current + 1 : 0;
	if (peek())
	{
		if (tokens[nextTokenIndex].type == TokenType::MUL)
		{
			advance(); // move to operator
			advance(); // move to possible next Oprand
			rightOprand = factor();
			leftOprand  = leftOprand * rightOprand;
		}
		else if (tokens[nextTokenIndex].type == TokenType::DIV)
		{
			advance(); // move to operator
			advance(); // move to possible next Oprand
			rightOprand = factor();
			leftOprand  = leftOprand / rightOprand;
		}
	}

	return leftOprand;
}

double Parser::factor()
{
	bool unaryMinus = false;
	double number;
	switch (tokens[current].type)
	{
	case TokenType::NUMBER:
		number = tokens[current].value;
		break;

	case TokenType::LPAREN:
		advance();
		number = expression();
		break;

	case TokenType::RPAREN:
		advance();
		number = 0;
		break;

	case TokenType::MINUS:
		unaryMinus = true;
		advance();
		number = factor();
		break;
	}

	if (unaryMinus) number *= -1;

	return number;
}
