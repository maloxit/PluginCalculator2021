#pragma once
#include "Defines.hpp"
#include "Expression.hpp"
#include "Shared/Token.hpp"

//RPNConverter class. Converts Expression from math notation to ReversePolishNotation using shunting-yard algorithm. 
class RPNConverter
{
private:
	Expression result;
	std::vector<ExpressionItem> stack;
	bool stackFlushToOpenBracketToResult();
	void stackFlushLowerPriorityToResult(InfixOperationToken* compareOp);
	void stackFlushPrefixUnarOperationsToResult();
	void stackPrefixOperationToResult();
	void processOperation(OperationToken* operation, ExpressionItem& item);
public:
	Expression&& convert(Expression& expression);
};