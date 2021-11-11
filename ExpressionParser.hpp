#pragma once
#include "Defines.hpp"
#include "Expression.hpp"
#include "LexemePluginLoader.hpp"

//ExpressionParser class. Composes an expression from the input string.
class ExpressionParser
{
private:
	Expression expression;
	//List of lexemes to parse
	LexemeVec& lexemeVec;
	size_t linePos;
	void parseValue(std::string& line);
	void parseLexeme(std::string& line);
	//Specifies all UnspecifiedOperationTokens
	void specify();
public:
	ExpressionParser(LexemeVec& lexemes);
	Expression&& parse(std::string& line);
};
