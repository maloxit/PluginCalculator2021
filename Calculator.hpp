// Calculator.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "Defines.hpp"
#include "Expression.hpp"
#include "StandartLexems.hpp"
#include "ExpressionParser.hpp"
#include "RPNConverter.hpp"
#include "Evaluator.hpp"
#include "LexemePluginLoader.hpp"


class Calculator
{
private:
	LexemeVec lexemeVec;
	LexemePluginLoader pluginLoader;
	ExpressionParser parser;
	RPNConverter converter;
	Evaluator evaluator;
	double calculateLine(std::string& line);
public:
	~Calculator();
	Calculator();
	//Loads already loaded or local plugin
	void importLexemeBase(LexemePluginImporter importer);
	//Loads all plugin dll's from dirPath directory
	void LoadLexemePlugins(const std::string& dirPath);
	//Run work cicle. lineMaxSize - maximum input line lenght, quitWord - key word to break work cicle.
	void Run(size_t lineMaxSize, const std::string& quitWord);
};
