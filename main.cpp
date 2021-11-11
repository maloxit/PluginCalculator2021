#include "Calculator.hpp"

using std::string;
using std::logic_error;
using std::exception;
using std::cout;

int main()
{
	try
	{
		Calculator calc;
		calc.LoadLexemePlugins(string("plugins/"));
		calc.Run(300, string("quit"));
	}
	catch (logic_error er)
	{
		cout << "Logic error: " << er.what() << std::endl;
	}
	catch (exception ex)
	{
		cout << "Unhandled exception: " << ex.what() << std::endl;
	}
	return 0;
}