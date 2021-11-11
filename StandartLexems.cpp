#include "StandartLexems.hpp"

using std::shared_ptr;
using std::make_shared;
using std::static_pointer_cast;
using std::string;
using std::vector;
using std::logic_error;



UnspecifiedMinus::UnspecifiedMinus() : UnspecifiedOperationToken(nullptr)
{
	unarMinusToken = make_shared<PrefixOperationToken>([](const vector<double>& vals) -> double
		{
			if (vals.size() != 1)
				throw logic_error("Incorrect number of arguments for math function.");
			return -vals.at(0);
		}, 1);
	binarMinusToken = make_shared<InfixOperationToken>([](const vector<double>& vals) -> double
		{
			if (vals.size() != 2)
				throw logic_error("Incorrect number of arguments for math function.");
			return vals.at(0) - vals.at(1);
		}, InfixOperationToken::Associativity::LEFT, PLUS_MINUS_PRESENDENCE);

}

OperationToken* UnspecifiedMinus::specify(ExpressionItem* left, ExpressionItem* right)
{
	if (left == nullptr || (!left->isValue() && left->token()->lexType == LexemeType::OPEN_BRACKET))
		return static_cast<OperationToken*>(unarMinusToken.get());
	else
		return static_cast<OperationToken*>(binarMinusToken.get());
}

void StandartLexemsImporter(LexemeVec& lexemeVec)
{
	lexemeVec.push_back(Lexeme(string("("), static_pointer_cast<Token>(make_shared<OpenBracketToken>())));
	lexemeVec.push_back(Lexeme(string(")"), static_pointer_cast<Token>(make_shared<CloseBracketToken>())));
	lexemeVec.push_back(Lexeme(string(","), static_pointer_cast<Token>(make_shared<ArgumentsSeparatorToken>())));
	lexemeVec.push_back(Lexeme(string("-"), static_pointer_cast<Token>(make_shared<UnspecifiedMinus>())));

	lexemeVec.push_back(Lexeme(string("+"), static_pointer_cast<Token>(make_shared<InfixOperationToken>(
		[](const vector<double>& vals) -> double
		{
			if (vals.size() != 2)
				throw logic_error("Incorrect number of arguments for math function.");
			return vals.at(0) + vals.at(1);
		}, InfixOperationToken::Associativity::LEFT, PLUS_MINUS_PRESENDENCE))));

	lexemeVec.push_back(Lexeme(string("*"), static_pointer_cast<Token>(make_shared<InfixOperationToken>(
		[](const vector<double>& vals) -> double
		{
			if (vals.size() != 2)
				throw logic_error("Incorrect number of arguments for math function.");
			return vals.at(0) * vals.at(1);
		}, InfixOperationToken::Associativity::LEFT, MUMT_DIV_PRESENDENCE))));

	lexemeVec.push_back(Lexeme(string("/"), static_pointer_cast<Token>(make_shared<InfixOperationToken>(
		[](const vector<double>& vals) -> double
		{
			if (vals.size() != 2)
				throw logic_error("Incorrect number of arguments for math function.");
			return vals.at(0) / vals.at(1);
		}, InfixOperationToken::Associativity::LEFT, MUMT_DIV_PRESENDENCE))));
}