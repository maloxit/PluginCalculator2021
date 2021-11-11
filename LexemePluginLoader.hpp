#pragma once
#include "Defines.hpp"
#include "Shared/Token.hpp"
#include <Windows.h>

#define LEXEME_PLUGIN_IMPORTER _importLexems

//dll plugin import type
using LexemePluginImporter = void(*)(LexemeVec& lexemeVec);

//LexemePluginLoader class. Manages the import of lexemes from dll plugins, loads and unloads them when destroyed.
class LexemePluginLoader
{
private:
	std::vector<HMODULE> loadedPlugins;
	std::vector<std::string> getPluginsFromDir(const std::string& dirPath);
	void importPluginToLexemeVec(HMODULE plugin, LexemeVec& lexemeVec);
public:
	~LexemePluginLoader();
	void loadPluginsFromDir(LexemeVec& lexemeVec, const std::string& dirPath);
};