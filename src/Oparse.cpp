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
	pair<string, string> splitParamAndValue(const string &configline)
	{
		vector<string> tokens;
		Oparse::SplitString(configline, tokens, "=");
		string key = Oparse::RemoveExtraWhiteSpace(tokens[0]);
		string value = tokens.size() > 1 ? Oparse::RemoveExtraWhiteSpace(tokens[1]) : "";
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
					it->second->ParseValue(keyValue.second);
				}
				catch (exception e)
				{
					result.AddError(e.what());
				}
			}
		}
	}



	OpInt *_Int(int & receiver)
	{
		return new OpInt(receiver);
	}

	OpFloat *_Float(float & receiver)
	{
		return new OpFloat(receiver);
	}

	OpDouble *_Double(double & receiver)
	{
		return new OpDouble(receiver);
	}

	OpString *_String(string & receiver)
	{
		return new OpString(receiver);
	}

	OpBool * _Bool(bool & receiver)
	{
		return new OpBool(receiver);
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
			result.AddError(ss.str());
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
			result.AddError(ss.str());
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
		return result;
	}
#endif
}




