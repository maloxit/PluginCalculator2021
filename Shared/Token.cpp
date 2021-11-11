#include "Token.hpp"

Token::Token(LexemeType lexType) : lexType(lexType) {};

OpenBracketToken::OpenBracketToken() : Token(LexemeType::OPEN_BRACKET) {};

CloseBracketToken::CloseBracketToken() : Token(LexemeType::CLOSE_BRACKET) {};

ArgumentsSeparatorToken::ArgumentsSeparatorToken() : Token(LexemeType::ARGUMENTS_SEPARATOR) {};

OperationToken::OperationToken(OperationType operationType, MathFunction func, uint argumentsCount) :
	Token(LexemeType::OPERATION), operationType(operationType), argumentsCount(argumentsCount), func(func) {};

InfixOperationToken::InfixOperationToken(MathFunction func, Associativity associativity, uint presendence) :
	OperationToken(OperationType::INFIX, func, 2), associativity(associativity), presendence(presendence) {};

PrefixOperationToken::PrefixOperationToken(MathFunction func, uint argumentsCount) : OperationToken(OperationType::PREFIX, func, argumentsCount) {};

PostfixOperationToken::PostfixOperationToken(MathFunction func, uint argumentsCount) : OperationToken(OperationType::POSTFIX, func, argumentsCount) {};

UnspecifiedOperationToken::UnspecifiedOperationToken(MathFunction func) : OperationToken(OperationType::UNSPECIFIED, func, 0) {};