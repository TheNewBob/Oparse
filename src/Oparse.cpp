#ifndef OPARSE_STANDALONE
#include "orbitersdk.h"
#else
#include <fstream>
#endif

#include "OpStdLibs.h"
#include "Oparse.h"
#include <algorithm>
#include <sstream>


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


	OpValue *GetParamFromMapping(const string key, const OpModelDef &mapping, vector<string> blocks)
	{
		auto it = mapping.find(key);
		if (it != mapping.end())
		{
			return it->second.first;
		}
		else
		{
			//see if the parameter is in a deeper block
			for (unsigned int i = blocks.size(); i > 0; --i)
			{
				auto block = mapping.find(blocks[i - 1]);
				if (block != mapping.end())
				{
					auto *model = dynamic_cast<OpModelValue*>(block->second.first);
					if (model != NULL)
					{
						return GetParamFromMapping(key, model->GetModelDef(), blocks);
					}
				}
			}
		}
		return NULL;
	}

	void parseParamValue(OpValue *parser, const string value, const string key, PARSINGRESULT &result)
	{
		if (parser != NULL)
		{
			try
			{
				parser->ParseValue(value);
			}
			catch (exception e)
			{
				result.AddError(key, e.what());
			}
		}
	}

	void parseLine(const string line, OpModelDef &mapping, PARSINGRESULT &result, vector<string> &blocks)
	{
		string l = line;
		// remove comments, i.e. everything left of a ;, as well as leading and trailing whitespace
		if (l.find_first_of(';') != std::string::npos)
			l.erase(line.find_first_of(';'), std::string::npos);
		l = RemoveExtraWhiteSpace(l);

		if (l != "")
		{
			string value = "";
			
			// Check if this is the beginning of a block, otherwise try to split the line into param and value.
			if (l.compare(0, 6,"BEGIN_") == 0)
			{
				// this is the start of a block. read the block name and continue.
				blocks.push_back(l.substr(6, l.length()));
			}
			else if (l.compare(0, 4, "END_") == 0)
			{
				if (blocks.size() > 0)
				{

					// magic to enable some syntactical sugar in the cfg (END_FOO closes block BEGIN_FOO BAR)
					vector<string> paramTokens;
					SplitString(l, paramTokens, "_ \t");
					if (paramTokens.size() == 0 || paramTokens[1] != blocks.back().substr(0, paramTokens[1].length()))
					{
						stringstream msg;
						msg << "Unexpected end of block: " << l << ". Expected END_" << blocks.back() << "!";
						result.AddError(blocks.back(), msg.str());
					}

					// delete the last element of readingBlock, since the block has closed.
					blocks.erase(blocks.begin() + (blocks.size() - 1));
				}
				else
				{
					result.AddError(OP_GENERAL_ERROR, "Unexpected end of block. No block has been opened!");
				}
			}
			else
			{
				if (StringContains(l, "="))
				{
					// This is a normal parameter, not a BlockList
					auto keyValue = splitParamAndValue(line);
					OpValue *parser = GetParamFromMapping(keyValue.first, mapping, blocks);
					parseParamValue(parser, keyValue.second, keyValue.first, result);
				}
				else
				{
					// Line contains no =, must be an item of a BlockList
					OpValue *parser = GetParamFromMapping(blocks.back(), mapping, blocks);
					parseParamValue(parser, l, blocks.back(), result);
				}
			}
		}
	}

	void clearModelDef(OpModelDef &mapping)
	{
/*		for (auto param = mapping.begin(); param != mapping.end(); ++param)
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
		mapping.clear();*/
	}

	/**
	 * Validates a parsed map using the provided validators.
	 */
	void validateParsedMap(OpModelDef &mapping, PARSINGRESULT &result)
	{
/*		for (auto param = mapping.begin(); param != mapping.end(); ++param)
		{
			// walk through all validators for each value. 
			OpValue *value = param->second.first;
			vector<OpValidator*> &validators = param->second.second;
			for (auto validator = validators.begin(); validator != validators.end(); ++validator)
			{
				(*validator)->Validate(value, param->first, result);
			}
		}*/
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
			vector<string> blocks;

			while (getline(file, line))
			{
				parseLine(line, mapping, result, blocks);
			}

			if (blocks.size() > 0)
			{
				result.AddError(OP_GENERAL_ERROR, "Unexpected end of file. Some blocks have not been closed!");
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




