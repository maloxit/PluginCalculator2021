#include "..\Defines.hpp"
#include "..\LexemePluginLoader.hpp"
#include "..\Expression.hpp"
#include <Windows.h>
#include <cmath>

using std::shared_ptr;
using std::make_shared;
using std::static_pointer_cast;
using std::string;
using std::vector;
using std::logic_error;

//Power and exponent plugin
extern "C" __declspec(dllexport) void LEXEME_PLUGIN_IMPORTER(LexemeVec & lexemeVec)
{
	lexemeVec.push_back(Lexeme(string("exp"), static_pointer_cast<Token>(make_shared<PrefixOperationToken>([](const vector<double>& vals) -> double
		{
			if (vals.size() != 1)
				throw logic_error("Incorrect number of arguments for math function.");
			return exp(vals.at(0));
		}, 1))));
	lexemeVec.push_back(Lexeme(string("^"), static_pointer_cast<Token>(make_shared<InfixOperationToken>(
		[](const vector<double>& vals) -> double
		{
			if (vals.size() != 2)
				throw logic_error("Incorrect number of arguments for math function.");
			return pow(vals.at(0), vals.at(1));
		}, InfixOperationToken::Associativity::RIGHT, POW_PRESENDENCE))));
}