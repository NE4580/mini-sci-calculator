// lexer
#include "../include/lexer.hpp"
#include <cctype>
#include <cstddef>
#include <optional>
#include <ostream>
#include <string>

Lexer::Lexer(const std::string& text) : input(text) { position = 0; }

bool Lexer::isSymbol() const
{
	if (position < input.size())
	{
		if ((input[position] == '+') || (input[position] == '-') ||
		    (input[position] == '/') || (input[position] == '*') ||
		    (input[position] == '(') || (input[position] == ')') ||
		    input[position] == '!' || input[position] == '^')
			return true;
	}
	return false;
}

bool Lexer::endsvalue(TokenType tt) const
{
	if (tt == TokenType::NUMBER || tt == TokenType::RPAREN) return true;
	return false;
}

bool Lexer::startsValue(TokenType tt) const
{
	if (tt == TokenType::NUMBER || tt == TokenType::LPAREN || isFunction(tt))
		return true;
	return false;
}

bool Lexer::isFunction(TokenType tt) const
{
	if (tt == TokenType::FUNCTION) return true;
	return false;
}

std::vector<Token>& Lexer::getTokens() { return tokens; }

std::optional<Token> Lexer::readFunction()
{
	size_t next   = (position + 1 < input.size()) ? position + 1 : 0;
	size_t startI = position, insertIndex = 0;
	std::string value = "";

	if (!std::isalpha(input[position])) return std::nullopt;

	while (position < input.size())
	{
		if (std::isalpha(input[position]))
		{
			value.insert(insertIndex++, 1,
			             input[position]); // make a string of the whole number

			position += (position < input.size()) ? 1 : 0;
			next += (next < input.size()) ? 1 : 0;
		}
		else
			break;
	}

	for (char& c : value)
		c = std::tolower(c); // convert to lowercase to gaurd against character case

	if (value == "sin")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "cos")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "tan")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "asin")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "acos")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "atan")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "sqrt")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else if (value == "cbrt")
		return Token{TokenType::FUNCTION, false, startI, 0.0F, value.c_str()};
	else
		return std::nullopt;
}

std::optional<Token> Lexer::readNumber()
{
	size_t next   = (position + 1 < input.size()) ? position + 1 : 0;
	size_t startI = position, insertIndex = 0, decimalCount = 0;
	std::string value = "";

	if (!std::isdigit(input[position]) && !(input[position] == '.'))
		return std::nullopt;

	while (position < input.size())
	{
		if (input[position] == '.' && input[next] == '.')
			return Token{TokenType::ERROR, false, position, 0.0F};

		else if (std::isdigit(input[position]) || input[position] == '.')
		{
			if (input[position] == '.') decimalCount++;

			// consume numbers as long as there is at most one decimal point
			if (decimalCount <= 1)
			{
				value.insert(insertIndex++, 1,
				             input[position]); // make a string of the whole number

				position += (position < input.size()) ? 1 : 0;
				next += (next < input.size()) ? 1 : 0;
			}
			else
				return Token{TokenType::ERROR, false, position, 0.0F};
		}

		else
			break;
	}

	return Token{TokenType::NUMBER, (decimalCount == 1) ? true : false, startI,
	             std::stod(value)};
}

std::optional<Token> Lexer::readSymbol()
{
	char value;
	int startI = position;

	if (isSymbol())
	{
		value = input[position];
		position += (position < input.size()) ? 1 : 0;
		return tokenizeSymbol(value, startI);
	}
	else
		return std::nullopt;
}

Token Lexer::tokenizeSymbol(const char val, size_t beg)
{
	TokenType tokenType;

	if (val == '+')
		tokenType = TokenType::PLUS;

	else if (val == '-')
		tokenType = TokenType::MINUS;

	else if (val == '*')
		tokenType = TokenType::MUL;

	else if (val == '/')
		tokenType = TokenType::DIV;

	else if (val == '^')
		tokenType = TokenType::PWR;

	else if (val == '!')
		tokenType = TokenType::FACTORIAL;

	else if (val == '(')
		tokenType = TokenType::LPAREN;

	else if (val == ')')
		tokenType = TokenType::RPAREN;

	else
		tokenType = TokenType::ERROR;

	return Token{tokenType, false, beg, 0.0F};
}

bool Lexer::createTokens()
{
	bool success = true;
	while (position < input.size())
	{
		if (std::isspace(input[position])) // skip whitespace
		{
			++position;
			continue;
		}

		std::optional<Token> token;

		if (std::isdigit(input[position]) || input[position] == '.')
			token = readNumber();

		else if (std::isalpha(input[position]))
			token = readFunction();

		else
			token = readSymbol();

		if (!token.has_value()) // handle nullopt
		{
			std::cerr << "ERROR: Unexpected character at postion $" << position
			          << ". " << std::endl;
			success = false;
			break;
		}

		if (token->type == TokenType::ERROR) // error tokens
		{
			std::cerr << "Lexer error at $" << token->position << ". " << std::endl;
			success = false;
			break;
		}
		// otherwise push the token
		tokens.push_back(*token);
	}
	return success;
}

void Lexer::translateImplicitMul()
{
	std::vector<Token> result;

	for (size_t x = 0; x < tokens.size(); x++)
	{
		result.push_back(tokens[x]);
		if (x + 1 < tokens.size())
		{
			if (endsvalue(tokens[x].type) && startsValue(tokens[x + 1].type))
			{
				result.push_back(Token{TokenType::MUL, false, x, 0.0F});
			}
		}
	}
	tokens = std::move(result);
}

void Lexer::showTokens() const
{
	std::cout << "Total Tokens: " << tokens.size() << std::endl;
	for (const auto& token : tokens)
		if (token.type == TokenType::NUMBER)
			std::cout << "[TYPE: NUMBER (" << token.value
			          << ") | isRN: " << token.isFloat << " "
			          << " | INDEX (" << token.position << ") ]" << std::endl;

		else if (token.type == TokenType::FUNCTION)
			std::cout << "[TYPE: FUNCTION | "
			          << "INDEX (" << token.position << ") ]" << std::endl;

		else
			std::cout << "[TYPE: SYMBOL ("
			          << ((token.type == TokenType::LPAREN ||
			               token.type == TokenType::RPAREN)
			                  ? " PARENTHESES ) | "
			                  : "  OPERATOR   ) | ")
			          << "INDEX (" << token.position << ") ]" << std::endl;
}
