#include "Evaluator.hpp"

using std::logic_error;
using std::exception;

void Evaluator::extractArguments(uint argumentsCount)
{
	argumentsVec.clear();
	argumentsVec.resize(argumentsCount);
	for (int i = argumentsCount - 1; i >= 0; i--)
	{
		if (stack.empty())
			throw exception("To few arguments for operation.");
		argumentsVec[i] = stack.back();
		stack.pop_back();
	}
}
double Evaluator::processOperation(OperationToken* operation)
{
	switch (operation->operationType)
	{
	case OperationToken::OperationType::PREFIX:
	case OperationToken::OperationType::INFIX:
	case OperationToken::OperationType::POSTFIX:
		extractArguments(operation->argumentsCount);
		return operation->func(argumentsVec);
	case OperationToken::OperationType::UNSPECIFIED:
		throw logic_error("Unhandled unspecified operation.");
	default:
		throw logic_error("Invalid OperationType.");
	}
}
double Evaluator::evaluate(Expression& expression)
{
	stack.clear();
	for (auto& item : expression)
	{
		if (item.isValue())
		{
			stack.push_back(item.val());
			continue;
		}
		Token* token = item.token();
		switch (token->lexType)
		{
		case Token::LexemeType::OPERATION:
			stack.push_back(processOperation(static_cast<OperationToken*>(token)));
			break;
		case Token::LexemeType::ARGUMENTS_SEPARATOR:
		case Token::LexemeType::OPEN_BRACKET:
		case Token::LexemeType::CLOSE_BRACKET:
			throw logic_error("Expression was not properly converted before evaluation.");
		default:
			throw logic_error("Invalid LexemeType.");
		}
	}
	if (stack.size() != 1)
		throw exception("To many arguments for operation.");
	return stack.back();
}