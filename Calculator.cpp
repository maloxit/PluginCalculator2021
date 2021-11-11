// Calculator.cpp : Defines the entry point for the application.
//

#include "Calculator.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::logic_error;
using std::exception;


double Calculator::calculateLine(string& line)
{
	Expression expression = parser.parse(line);
	Expression expressionRPN = converter.convert(expression);
	return evaluator.evaluate(expressionRPN);
}
Calculator::Calculator() : parser(lexemeVec)
{
	StandartLexemsImporter(lexemeVec);
}
Calculator::~Calculator()
{
	//All exturnal Tokens must be destroyed before freeing dll's
	lexemeVec.clear();
}
void Calculator::LoadLexemePlugins(const string& dirPath)
{
	pluginLoader.loadPluginsFromDir(lexemeVec, dirPath);
}
void Calculator::importLexemeBase(LexemePluginImporter importer)
{
	importer(lexemeVec);
}
void Calculator::Run(size_t lineMaxSize, const string& quitWord)
{
	string line(300, '\0');
	while (true)
	{
		cout << "Input expression or \"" << quitWord << "\" to quit:" << endl;
		std::getline(cin, line);
		if (!cin || line == quitWord)
			return;
		try
		{
			double result = calculateLine(line);
			cout << "Result: " << result << endl;
		}
		catch (logic_error& er)
		{
			throw er;
		}
		catch (exception& ex)
		{
			cout << "Incorrect input: " << ex.what() << endl;
		}
	} 
}
