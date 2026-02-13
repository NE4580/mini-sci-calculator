#include "parser.hpp"
#include "tables.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

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
	    match(TokenType::MUL) || match(TokenType::DIV) ||
	    match(TokenType::MOD)) // if operator is a match, move past the operator
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

		else if (op == TokenType::MOD)
		{
			leftOprand->number = std::fmod(leftOprand->number, rightOprand->number);
			std::abs(leftOprand->number);
		}
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

std::optional<Value> Parser::getConstant(const std::string name) const
{
	auto it = CONSTANTS_TABLE.find(name);

	if (it == CONSTANTS_TABLE.end()) return std::nullopt;

	return Value{it->second, true};
}

std::optional<Value> Parser::function(std::string name,
                                      std::vector<double>& args)
{
	// ====================intentionally left in========================
	//  static const std::unordered_map<std::string, FunctionMetaData> dispatcher
	//  =
	//  {
	//      {"sin", [this](auto& args) { return sin(toRadians(args[0])); }},
	//      {"cos", [this](auto& args) { return cos(toRadians(args[0])); }},
	//      {"tan", [this](auto& args) { return tan(toRadians(args[0])); }},
	//      {"asin", [this](auto& args) { return fromRadians(asin(args[0])); }},
	//      {"acos", [this](auto& args) { return fromRadians(acos(args[0])); }},
	//      {"atan", [this](auto& args) { return fromRadians(atan(args[0])); }},
	//      {"sqrt", [](auto& args) { return sqrt(args[0]); }},
	//      {"cbrt", [](auto& args) { return cbrt(args[0]); }},
	//  };
	//
	//  auto inTable = dispatcher.find(name);
	//  if (inTable == dispatcher.end()) return std::nullopt;
	//
	//  return Value{inTable->second(args), true};
	auto it = FUNCTIONS_TABLE.find(name);
	if (it == FUNCTIONS_TABLE.end()) return std::nullopt;

	// arity check
	int expectedArgc = it->second.arity;
	int given        = (int)args.size();

	if (expectedArgc != given)
	{
		std::cerr << "ERROR: Unmatched argument count for \'" << name
		          << "\' expected " << expectedArgc << " arguments; got " << given
		          << "\n";
		return std::nullopt;
	}

	return Value{it->second.fn(args), true};
}

std::optional<Value> Parser::factor() { return primary(); }

std::optional<std::vector<double>> Parser::parseArguments()
{
	std::vector<double> argVect;

	auto first = expression();
	if (!first) return std::nullopt;
	argVect.push_back(first->number);

	while (currentToken() && currentToken()->type == TokenType::COMMA)
	{
		advance(); // consume ,
		auto next = expression();
		if (!next) return std::nullopt;
		argVect.push_back(next->number);
	}

	return argVect;
}

std::optional<Value> Parser::parseFuntionCall(const std::string& name)
{
	if (!isOpeningPren()) return std::nullopt;
	advance(); // consume (
	auto args = parseArguments();
	if (!args.has_value()) return std::nullopt;
	if (!isClosingPren()) return std::nullopt;

	if (!isClosingPren()) return std::nullopt;
	advance(); // consume )
	return function(name, args.value());
}

std::optional<Value> Parser::resolveIdentifier(const std::string& name)
{
	if (auto constant = getConstant(name)) return constant; // get constants

	auto it = FUNCTIONS_TABLE.find(name); // lookup function

	// check if unary using arity of function
	if (it != FUNCTIONS_TABLE.end()) // unary function guard
	{
		short arity = it->second.arity;

		if (arity == 1)
		{
			std::vector<double> functionArgs;

			auto arg = unary();
			if (!arg) return std::nullopt;

			functionArgs.push_back(arg->number);
			if (arg) return function(name, functionArgs);
		}

		std::cerr << "ERROR: function \'" << name << "\' requires parentheses\n";
		return std::nullopt;
	}

	std::cerr << "ERROR: unknown identifier \'" << name << "\'\n";
	return std::nullopt; // unknown identifier
}

std::optional<Value> Parser::parseFuntionOrConstant()
{
	std::string name = currentToken()->fname;
	advance(); // consume identifier

	if (isOpeningPren()) return parseFuntionCall(name); // call function call

	return resolveIdentifier(name);
}

std::optional<Value> Parser::primary()
{
	if (!currentToken()) return std::nullopt;

	if (currentToken()->type == TokenType::NUMBER)
	{
		Value v{currentToken()->value, currentToken()->isFloat};
		advance();
		return v;
	}

	if (currentToken()->type == TokenType::LPAREN)
	{
		advance(); // consume (
		auto expValue = expression();
		if (!expValue || !isClosingPren()) return std::nullopt;
		advance();
		return expValue;
	}

	if (currentToken()->type == TokenType::IDENTIFIER)
	{
		return parseFuntionOrConstant();
	}

	return std::nullopt;
}
