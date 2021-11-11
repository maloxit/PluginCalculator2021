#include "Expression.hpp"

using std::logic_error;

bool ExpressionItem::isValue() { return _isValue; };
double ExpressionItem::val()
{
	if (!_isValue)
		throw logic_error("ExpressionItem data access violation.");
	return _val;
}
Token* ExpressionItem::token()
{
	if (_isValue)
		throw logic_error("ExpressionItem data access violation.");
	return _token;
}
ExpressionItem::ExpressionItem(double val) : _isValue(true), _val(val) {};
ExpressionItem::ExpressionItem(Token* token) : _isValue(false), _token(token) {};