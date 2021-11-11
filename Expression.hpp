#pragma once
#include "Defines.hpp"

class Token;

//ExpressionItem class. Allows generalized storage of both values and tokens with secure access.
class ExpressionItem
{
private:
	bool _isValue;
	union {
		double _val;
		Token* _token;
	};
public:
	bool isValue();
	double val();
	Token* token();
	ExpressionItem() = delete;
	ExpressionItem(double val);
	ExpressionItem(Token* token);
};

using Expression = std::vector<ExpressionItem>;