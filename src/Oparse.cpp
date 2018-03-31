#ifndef OPARSE_STANDALONE
#include "orbitersdk.h"
#else
#include <fstream>
#endif

#include "OpStdLibs.h"
#include "Oparse.h"
#include <algorithm>


namespace Oparse
{
	const string OP_GENERAL_ERROR = "OP_GENERAL";

	pair<string, string> splitParamAndValue(const string &configline)
	{
		vector<string> tokens;
		SplitString(configline, tokens, "=");
		string key = RemoveExtraWhiteSpace(tokens[0]);
		string value = tokens.size() > 1 ? RemoveExtraWhiteSpace(tokens[1]) : "";
		return make_pair(key, value);
	}

	void parseLine(const string line, OpModelDef &mapping, PARSINGRESULT &result)
	{
		string l = line;
		// remove comments, i.e. everything left of a ;
		if (l.find_first_of(';') != std::string::npos)
			l.erase(line.find_first_of(';'), std::string::npos);

		if (l != "")
		{
			auto keyValue = splitParamAndValue(l);
			auto it = mapping.find(keyValue.first);
			if (it != mapping.end())
			{
				try
				{
					it->second.first->ParseValue(keyValue.second);
				}
				catch (exception e)
				{
					result.AddError(it->first, e.what());
				}
			}
		}
	}

	void clearModelDef(OpModelDef &mapping)
	{
		for (auto param = mapping.begin(); param != mapping.end(); ++param)
		{
			OpValue *value = param->second.first;
			vector<OpValidator*> validators = param->second.second;

			// delete the values and the validators of this map.
			delete value;
			for (unsigned int i = 0; i < validators.size(); ++i)
			{
				delete validators[i];
			}
			validators.clear();
		}
		mapping.clear();
	}

	/**
	 * Validates a parsed map using the provided validators.
	 */
	void validateParsedMap(OpModelDef &mapping, PARSINGRESULT &result)
	{
		for (auto param = mapping.begin(); param != mapping.end(); ++param)
		{
			// walk through all validators for each value. 
			OpValue *value = param->second.first;
			vector<OpValidator*> &validators = param->second.second;
			for (auto validator = validators.begin(); validator != validators.end(); ++validator)
			{
				(*validator)->Validate(value, param->first, result);
			}
		}
	}

#ifdef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping)
	{
		PARSINGRESULT result;
		ifstream file;
		file.open(path);

		if (!file.is_open())
		{
			stringstream ss;
			ss << "Could not open file: " << path;
			result.AddError(OP_GENERAL_ERROR, ss.str());
			return result;
		}
		else
		{
			string line;
			vector<string> tokens;
			bool readdata = false;

			while (getline(file, line))
			{
				parseLine(line, mapping, result);
			}
		}
		validateParsedMap(mapping, result);
		clearModelDef(mapping);
		return result;
	}
#else

	void resetFile(FILEHANDLE file)
	{
		char l[500];
		oapiReadItem_string(file, (char*)"Module", l);
	}

	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root)
	{
		auto file = oapiOpenFile(path.data(), FILE_IN_ZEROONFAIL, root);
		if (file == NULL)
		{
			PARSINGRESULT result;
			stringstream ss;
			ss << "Could not open file: " << path;
			result.AddError(OP_GENERAL_ERROR, ss.str());
			return result;
		}
		else
		{
			return ParseFile(file, mapping);
		}
	}

	PARSINGRESULT ParseFile(FILEHANDLE file, OpModelDef &mapping)
	{
		PARSINGRESULT result;
		resetFile(file);
		char *l;
		while (oapiReadScenario_nextline(file, l))
		{
			parseLine(l, mapping, result);
		}
		validateParsedMap(mapping, result);
		clearModelDef(mapping);
		return result;
	}
#endif
}




