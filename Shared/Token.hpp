#pragma once
#include "..\Defines.hpp"


using MathFunction = double(*)(const std::vector<double>& vals);

#define PLUS_MINUS_PRESENDENCE 2
#define MUMT_DIV_PRESENDENCE 5
#define POW_PRESENDENCE 8

class ExpressionItem;

//Token base class. Used for generalization of punctuation tokens and operation tokens.
class Token
{
public:
	enum class LexemeType
	{
		OPERATION,
		OPEN_BRACKET,
		CLOSE_BRACKET,
		ARGUMENTS_SEPARATOR,
	};
	const LexemeType lexType;
	Token() = delete;
protected:
	Token(LexemeType lexType);
};

//Lexem type. Represents a token, assosiated with some key word
using Lexeme = std::pair<std::string, std::shared_ptr<Token>>;
using LexemeVec = std::vector<Lexeme>;

//Open Bracket punctuation token class.
class OpenBracketToken : public Token
{
public:
	OpenBracketToken();
};

//Close Bracket punctuation token class.
class CloseBracketToken : public Token
{
public:
	CloseBracketToken();
};

//Arguments Separator punctuation token class.
class ArgumentsSeparatorToken : public Token
{
public:
	ArgumentsSeparatorToken();
};

//OperationToken base class. Used for generalization of prefix, infix and postfix operations for evaluation in ReversePolishNotation.
class OperationToken : public Token
{
public:
	enum class OperationType
	{
		UNSPECIFIED,
		PREFIX,
		POSTFIX,
		INFIX
	};
	const OperationType operationType;
	MathFunction const func;
	const uint argumentsCount;
	OperationToken() = delete;
protected:
	OperationToken(OperationType operationType, MathFunction func, uint argumentsCount);
};

//InfixOperationToken class. Used for evaluation and convertion to ReversePolishNotation of infix math operations.
class InfixOperationToken : public OperationToken
{
public:
	enum class Associativity
	{
		LEFT,
		RIGHT
	};
	const Associativity associativity;
	const int presendence;
	InfixOperationToken() = delete;
	InfixOperationToken(MathFunction func, Associativity associativity, uint presendence);
};

//PrefixOperationToken class. Used for evaluation and convertion to ReversePolishNotation of prefix math operations(functions).
class PrefixOperationToken : public OperationToken
{
public:
	PrefixOperationToken() = delete;
	PrefixOperationToken(MathFunction func, uint argumentsCount);
};

//PostfixOperationToken class. Used for evaluation and convertion to ReversePolishNotation of postfix math operations
class PostfixOperationToken : public OperationToken
{
public:
	PostfixOperationToken() = delete;
	PostfixOperationToken(MathFunction func, uint argumentsCount);
};

//Base class for UnspecifiedOperation tokens. Used for lexemes, that define multiple operations based on context.
//When the left and right neighboring elements are defined, it should return a pointer to OperationToken to which it should be replaced
class UnspecifiedOperationToken : public OperationToken
{
public:
	virtual OperationToken* specify(ExpressionItem* left, ExpressionItem* right) = 0;
	UnspecifiedOperationToken() = delete;
	UnspecifiedOperationToken(MathFunction func);
};

