#include "RPNConverter.hpp"

using std::logic_error;
using std::exception;
using std::move;

bool RPNConverter::stackFlushToOpenBracketToResult()
{
	while (!stack.empty())
	{
		ExpressionItem item = stack.back();
		if (!item.isValue())
		{
			Token* token = item.token();
			if (token->lexType == Token::LexemeType::OPEN_BRACKET)
				break;
		}
		stack.pop_back();
		result.push_back(item);
	}
	return !stack.empty();
}
void RPNConverter::stackFlushLowerPriorityToResult(InfixOperationToken* compareOp)
{
	while (!stack.empty())
	{
		ExpressionItem item = stack.back();
		if (item.isValue())
			break;
		Token* token = item.token();
		if (token->lexType != Token::LexemeType::OPERATION)
			break;
		OperationToken* operation = static_cast<OperationToken*>(token);
		if (operation->operationType != OperationToken::OperationType::INFIX)
			break;
		InfixOperationToken* infixOp = static_cast<InfixOperationToken*>(operation);
		infixOp->presendence; infixOp->associativity;
		if (infixOp->presendence < compareOp->presendence ||
			(infixOp->presendence == compareOp->presendence && compareOp->associativity == InfixOperationToken::Associativity::RIGHT))
			break;
		stack.pop_back();
		result.push_back(item);
	}
}
void RPNConverter::stackFlushPrefixUnarOperationsToResult()
{
	while (!stack.empty())
	{
		ExpressionItem item = stack.back();
		if (item.isValue())
			break;
		Token* token = item.token();
		if (token->lexType != Token::LexemeType::OPERATION)
			break;
		OperationToken* operation = static_cast<OperationToken*>(token);
		if (operation->operationType == OperationToken::OperationType::PREFIX && operation->argumentsCount == 1)
		{
			stack.pop_back();
			result.push_back(item);
		}
		else
			break;
	}
}
void RPNConverter::stackPrefixOperationToResult()
{
	if (stack.empty())
		return;
	ExpressionItem item = stack.back();
	if (item.isValue())
		return;
	Token* token = item.token();
	if (token->lexType == Token::LexemeType::OPERATION &&
		static_cast<OperationToken*>(token)->operationType == OperationToken::OperationType::PREFIX)
	{
		stack.pop_back();
		result.push_back(item);
		stackFlushPrefixUnarOperationsToResult();
	}
}
void RPNConverter::processOperation(OperationToken* operation, ExpressionItem& item)
{
	switch (operation->operationType)
	{
	case OperationToken::OperationType::UNSPECIFIED:
		throw logic_error("Unhandled unspecified operation.");
	case OperationToken::OperationType::PREFIX:
		stack.push_back(item);
		break;
	case OperationToken::OperationType::INFIX:
		stackFlushLowerPriorityToResult(static_cast<InfixOperationToken*>(operation));
		stack.push_back(item);
		break;
	case OperationToken::OperationType::POSTFIX:
		result.push_back(item);
		break;
	default:
		throw logic_error("Invalid OperationType.");
	}
}
Expression&& RPNConverter::convert(Expression& expression)
{
	result.clear();
	stack.clear();
	for (auto& item : expression)
	{
		if (item.isValue())
		{
			result.push_back(item);
			stackFlushPrefixUnarOperationsToResult();
			continue;
		}
		Token* token = item.token();
		switch (token->lexType)
		{
		case Token::LexemeType::OPERATION:
		{
			processOperation(static_cast<OperationToken*>(token), item);
			break;
		}
		case Token::LexemeType::ARGUMENTS_SEPARATOR:
		{
			if (!stackFlushToOpenBracketToResult())
				throw exception("Missing arguments separator(comma) or open bracket.");
			break;
		}
		case Token::LexemeType::OPEN_BRACKET:
		{
			stack.push_back(item);
			break;
		}
		case Token::LexemeType::CLOSE_BRACKET:
		{
			if (!stackFlushToOpenBracketToResult())
				throw exception("Missing open bracket.");
			stack.pop_back();
			stackPrefixOperationToResult();
			break;
		}
		default:
			throw logic_error("Invalid LexemeType.");
		}
	}
	if (stackFlushToOpenBracketToResult())
		throw exception("Missing close bracket.");
	return move(result);
}