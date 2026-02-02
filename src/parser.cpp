#include "../include/parser.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

using std::function;

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

bool Parser::isOpeningPren()
{
	if (!currentToken()) return false;
	if (!(currentToken()->type == TokenType::LPAREN)) return false;
	return true;
}

double Parser::toRadians(double angle) { return angle * M_PIf / 180.0F; }
double Parser::fromRadians(double angle) { return angle * 180 / M_PIf; }

bool Parser::isClosingPren()
{
	if (!currentToken()) return false;
	if (!(currentToken()->type == TokenType::RPAREN)) return false;
	return true;
}

bool Parser::isFunction(TokenType tt) const
{
	if (tt == TokenType::IDENTIFIER) return true;
	return false;
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

		rightOprand = unary();

		if (!rightOprand) return std::nullopt;

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
	std::optional<Value> leftOprand = unary();
	std::optional<Value> rightOprand;

	if (!leftOprand) return std::nullopt;

	while (
	    match(TokenType::MUL) ||
	    match(TokenType::DIV)) // if operator is a match, move past the operator
	{
		TokenType op = currentToken()->type; // Coleect token type directly
		advance();                           // consume operator

		rightOprand = unary();

		if (!rightOprand) // break out if no oprand
			return std::nullopt;

		if (op == TokenType::MUL)
			leftOprand->number = leftOprand->number * rightOprand->number;

		else if (op == TokenType::DIV)
			leftOprand->number = leftOprand->number / rightOprand->number;

		leftOprand->isFloat = leftOprand->isFloat || rightOprand->isFloat;
	}
	return leftOprand;
}

std::optional<Value> Parser::unary()
{
	if (!currentToken()) return std::nullopt;

	if (currentToken()->type == TokenType::PLUS)
	{
		advance();
		return unary();
	}
	else if (currentToken()->type == TokenType::MINUS)
	{
		advance();
		auto num = unary();
		if (!num) return std::nullopt;

		num->number = -num->number; // negate
		return num;
	}
	else
		return power();
}

std::optional<Value> Parser::power()
{
	std::optional<Value> value = postfix();

	if (!value) return std::nullopt;

	if (!currentToken()) return value;

	if (currentToken()->type == TokenType::PWR)
	{
		advance(); // consume ^
		std::optional<Value> exponent = power();

		if (exponent)
			value->number = std::pow(value->number, exponent->number);
		else
			return std::nullopt;
	}
	return value;
}

static double factorial(double n)
{
	double fact = 1;
	if (n < 0 || std::floor(n) != n) return NAN; // reject non ints

	for (int x = 1; x <= (int)n; x++) fact *= x;

	return fact;
}
std::optional<Value> Parser::postfix()
{
	std::optional<Value> factNum = factor();

	if (!factNum) return std::nullopt;

	while (currentToken() && currentToken()->type == TokenType::FACTORIAL)
	{
		advance();
		// apply mathematical check to allow integers of value X.0
		if (factNum->number < 0.0F ||
		    std::floor(factNum->number) != factNum->number)
			return std::nullopt;

		double f = factorial(factNum->number);

		if (std::isnan(f)) return std::nullopt;

		factNum->number = f;

		if (!currentToken()) break; // exit when at end of input
	}
	return factNum;
}

std::optional<Value> Parser::function(std::string tt, double x)
{
	// alias to replace typing std::function<...>
	using funcTypeAlias = std::function<double(double)>;

	static const std::unordered_map<std::string, funcTypeAlias> dispatcher = {
	    {"sin", [this](double arg) { return sin(toRadians(arg)); }},
	    {"cos", [this](double arg) { return cos(toRadians(arg)); }},
	    {"tan", [this](double arg) { return tan(toRadians(arg)); }},
	    {"asin", [this](double arg) { return fromRadians(asin(arg)); }},
	    {"acos", [this](double arg) { return fromRadians(acos(arg)); }},
	    {"atan", [this](double arg) { return fromRadians(atan(arg)); }},
	    {"sqrt", [](double arg) { return sqrt(arg); }},
	    {"cbrt", [](double arg) { return cbrt(arg); }},
	};

	auto inTable = dispatcher.find(tt);
	if (inTable == dispatcher.end()) return std::nullopt;

	return Value{inTable->second(x), true};
}

std::optional<Value> Parser::factor()
{
	std::optional<Value> number;

	if (!currentToken()) return std::nullopt;

	if (currentToken()->type == TokenType::NUMBER)
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
		advance(); // consume )
	}
	else if (isFunction(currentToken()->type))
	{
		auto name = currentToken()->fname;
		advance(); // consume function name
		if (!isOpeningPren()) return std::nullopt;
		advance(); // consume (

		auto expResult = expression();

		// fail if nullopt or currentToken not ) after call to expression
		if (!expResult || !isClosingPren()) return std::nullopt;
		advance(); // consume )

		number = function(name, expResult->number);
		if (!number) return std::nullopt;
	}
	else
		return std::nullopt;

	return number;
}
