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

//Trigonomery plugin, that contains trigonometry operations
extern "C" __declspec(dllexport) void LEXEME_PLUGIN_IMPORTER(LexemeVec& lexemeVec)
{
	lexemeVec.push_back(Lexeme(string("sin"), static_pointer_cast<Token>(make_shared<PrefixOperationToken>([](const vector<double>& vals) -> double
		{
			if (vals.size() != 1)
				throw logic_error("Incorrect number of arguments for math function.");
			return sin(vals.at(0));
		}, 1))));
	lexemeVec.push_back(Lexeme(string("cos"), static_pointer_cast<Token>(make_shared<PrefixOperationToken>([](const vector<double>& vals) -> double
		{
			if (vals.size() != 1)
				throw logic_error("Incorrect number of arguments for math function.");
			return cos(vals.at(0));
		}, 1))));
	lexemeVec.push_back(Lexeme(string("tg"), static_pointer_cast<Token>(make_shared<PrefixOperationToken>([](const vector<double>& vals) -> double
		{
			if (vals.size() != 1)
				throw logic_error("Incorrect number of arguments for math function.");
			return tan(vals.at(0));
		}, 1))));
}