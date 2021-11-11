#include "ExpressionParser.hpp"


using std::string;
using std::exception;
using std::move;
using std::shared_ptr;

void ExpressionParser::parseValue(string& line)
{
	size_t endIndex;
	double val = stod(line.substr(linePos), &endIndex);
	expression.push_back(ExpressionItem(val));
	linePos += endIndex;
}
void ExpressionParser::parseLexeme(string& line)
{
	shared_ptr<Token> bestLexeme;
	size_t bestLen = 0;
	for (auto&& pair : lexemeVec)
	{
		if (pair.first.size() > bestLen && 0 == line.compare(linePos, pair.first.size(), pair.first))
		{
			bestLen = pair.first.size();
			bestLexeme = pair.second;
		}
	}
	if (bestLen == 0 || bestLexeme == nullptr)
	{
		expression.clear();
		throw exception("Unlisted lexeme used.");
	}
	expression.push_back(ExpressionItem(bestLexeme.get()));
	linePos += bestLen;
}
ExpressionParser::ExpressionParser(LexemeVec& lexemes) : lexemeVec(lexemes)
{
	linePos = 0;
}
void ExpressionParser::specify()
{
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (expression[i].isValue())
			continue;
		Token* token = expression[i].token();
		if (token->lexType != Token::LexemeType::OPERATION)
			continue;
		OperationToken* operation = static_cast<OperationToken*>(token);
		if (operation->operationType == OperationToken::OperationType::UNSPECIFIED)
		{
			ExpressionItem* left = (i == 0) ? nullptr : &expression[i - 1];
			ExpressionItem* right = (i + 1 == expression.size()) ? nullptr : &expression[i + 1];
			Token* specifiedLexeme = static_cast<UnspecifiedOperationToken*>(operation)->specify(left, right);
			expression[i] = ExpressionItem(specifiedLexeme);
		}
	}
}
Expression&& ExpressionParser::parse(string& line)
{
	expression.clear();
	linePos = 0;
	while (linePos < line.size())
	{
		if (isspace(line[linePos]))
		{
			linePos++;
			continue;
		}
		switch (line[linePos])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			parseValue(line);
			break;
		default:
			parseLexeme(line);
			break;
		}
	}
	specify();
	return move(expression);
}