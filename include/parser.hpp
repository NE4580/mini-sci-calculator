// Parser

#pragma once
#include "token.hpp"
#include <functional>
#include <optional>
#include <string>
#include <vector>

struct Value
{
	double number;
	bool isFloat;
};

struct FunctionMetaData
{
	int arity;
	std::function<double(const std::vector<double>&)> fn;
};

class Parser
{
private:
	size_t tokenIndex;
	std::vector<Token> tokens;

public:
	explicit Parser(const std::vector<Token>& t);
	double evalute();

private:
	std::optional<Token> peek();
	std::optional<Token> currentToken() const;
	void advance();
	bool match(TokenType tt);
	bool isOpeningPren();
	bool isClosingPren();
	// commented becuse they are implicitly handed by function(...), which handles
	// arity and lookup bool isFunction(TokenType tt) const; bool
	// isUnaryFunction(const std::string name); bool isMultiArgFunction(const
	// std::string name);
	double toRadians(double angle);
	double fromRadians(double angle);
	std::optional<Value> expression();
	std::optional<Value> term();
	std::optional<Value> primary();
	std::optional<Value> unary();
	std::optional<Value> power();
	std::optional<Value> postfix();
	std::optional<Value> factor();
	std::optional<Value> getConstant(const std::string name) const;
	std::optional<Value> function(std::string tt, std::vector<double>& args);
	std::optional<Value> parseFuntionCall(const std::string& name);
	std::optional<std::vector<double>> parseArguments();
	std::optional<Value> parseFuntionOrConstant();
};
