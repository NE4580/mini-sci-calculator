// Lexer.hpp

#pragma once
#include "token.hpp"
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

class Lexer
{
private:
	const std::string& input;
	size_t position;
	std::vector<Token> tokens;

	bool isSymbol() const;
	bool endsvalue(TokenType tt) const;
	bool startsValue(TokenType tt) const;
	bool isIdentifier(TokenType tt) const;

public:
	explicit Lexer(const std::string& text); // forbit inplicit conversions
	                                         // like Lexer t = "tf"
	std::vector<Token>& getTokens();
	std::optional<Token> readIdentifier();
	std::optional<Token> readNumber();
	std::optional<Token> readSymbol();
	std::optional<Token> readMod();
	Token tokenizeSymbol(const char val, size_t beg);
	bool createTokens();
	void translateImplicitMul(); // Inserts implicit multiplication on x(y) -> x*
	                             //(y) | (y)x -> (y) * x
	void showTokens() const;
};
