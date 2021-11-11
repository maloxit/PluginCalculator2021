#include "LexemePluginLoader.hpp"

#define TO_STRING(x) #x
#define MOCROS_VAL_TO_STRING(x) TO_STRING(x)

using std::string;
using std::vector;

vector<string> LexemePluginLoader::getPluginsFromDir(const string& dirPath)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE foundFile;
	string fullPath = dirPath + "*.dll";
	vector<string> pluginPaths;
	foundFile = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (foundFile != INVALID_HANDLE_VALUE) {
		pluginPaths.push_back(dirPath + fileInfo.cFileName);
		while (FindNextFile(foundFile, &fileInfo) != 0) {
			pluginPaths.push_back(dirPath + fileInfo.cFileName);
		}
	}
	return pluginPaths;
}
void LexemePluginLoader::importPluginToLexemeVec(HMODULE plugin, LexemeVec& lexemeVec)
{
	LexemePluginImporter importer = reinterpret_cast<LexemePluginImporter>(GetProcAddress(plugin, MOCROS_VAL_TO_STRING(LEXEME_PLUGIN_IMPORTER)));
	if (importer == NULL)
		return;
	importer(lexemeVec);
}
LexemePluginLoader::~LexemePluginLoader()
{
	for (auto& plugin : loadedPlugins)
	{
		FreeLibrary(plugin);
	}
}
void LexemePluginLoader::loadPluginsFromDir(LexemeVec& lexemeVec, const string& dirPath)
{
	vector<string> pluginPaths = getPluginsFromDir(dirPath);
	for (auto& path : pluginPaths)
	{
		HMODULE plugin = LoadLibraryA(path.c_str());
		loadedPlugins.push_back(plugin);
		importPluginToLexemeVec(plugin, lexemeVec);
	}
}