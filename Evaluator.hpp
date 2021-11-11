#pragma once
#include "Defines.hpp"
#include "Expression.hpp"
#include "Shared/Token.hpp"

//Evaluator class. Evaluates an Expression in ReversePolishNotation.
class Evaluator
{
private:
	std::vector<double> stack;
	std::vector<double> argumentsVec;
	void extractArguments(uint argumentsCount);
	double processOperation(OperationToken* operation);
public:
	double evaluate(Expression& expression);
};