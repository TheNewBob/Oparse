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


	OpValue *GetParamFromMapping(const string key, const OpModelDef &mapping)
	{
		auto it = mapping.find(key);
		if (it != mapping.end())
		{
			return it->second.first;
		}
		return NULL;
	}

	void ParseBlock(OpFile *file, OpModelDef &mapping, PARSINGRESULT &result)
	{
		string l;
		bool endOfBlock = false;
		string blockList = "";

		while (file->NextLine(l) && !endOfBlock)
		{
			string line = l;
			// remove comments, i.e. everything left of a ;, as well as leading and trailing whitespace
			if (line.find_first_of(';') != std::string::npos)
				line.erase(line.find_first_of(';'), std::string::npos);
			line = RemoveExtraWhiteSpace(line);

			if (line != "")
			{

				// Check if this is the beginning of a block
				if (line.compare(0, 6, "BEGIN_") == 0)
				{
					if (blockList != "")
					{
						result.AddError(OP_GENERAL_ERROR, "Block nested in BlockList is not allowed: " + line + ", aborting!");
						throw runtime_error("Abortied parsing due to fatal error!");
					}
					string blockname = line.substr(6, line.length());
					auto parser = GetParamFromMapping(blockname, mapping);
					if (parser != NULL)
					{
						// check if this is a nested value (model or modelfactory)
						auto nestable = dynamic_cast<OpNestable*>(parser);
						if (nestable != NULL)
						{
							// This block is a nested model. 
							nestable->ParseValue(file, result);
						}
						else
						{
							// this block is merely a BlockList, which doesn't require recursion.
							blockList = blockname;
						}
					}
					else
					{
						// this is a block that is not mapped.
						blockList = blockname;
					}
				}
				// Check if this is the end of a block
				else if (line.compare(0, 4, "END_") == 0)
				{
					if (blockList == "")
					{
						// The block we're currently recursing through has ended.
						endOfBlock = true;
					}
					else
					{
						// magic to enable some syntactical sugar in the cfg (END_FOO closes block BEGIN_FOO BAR)
						vector<string> paramTokens;
						SplitString(line, paramTokens, "_ \t");
						if (paramTokens.size() == 0 || paramTokens[1] != blockList.substr(0, paramTokens[1].length()))
						{
							result.AddError(blockList, "Unexpected end of block: " + line + ". Expected END_" + blockList + "!");
						}
						else
						{
							// reached end of current BlockList
							blockList = "";
						}
					}
				}
				else
				{
					if (blockList == "")
					{
						// We're not inside a BlockList.
						auto keyValue = splitParamAndValue(line);
						OpValue *parser = GetParamFromMapping(keyValue.first, mapping);
						if (parser != NULL)
							parser->ParseValue(keyValue.first, keyValue.second, result);
					}
					else
					{
						// Line contains no =, must be an item of a BlockList
						OpValue *parser = GetParamFromMapping(blockList, mapping);
						if (parser != NULL)
							parser->ParseValue(blockList, line, result);
					}
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
			// check if this is a nested value
			auto nestedValue = dynamic_cast<OpNestable*>(value);
			if (nestedValue != NULL)
			{
				nestedValue->Validate(result);
			}
		}
	}

	void parseFile(OpFile *file, OpModelDef &mapping, PARSINGRESULT &result)
	{
		try
		{
			ParseBlock(file, mapping, result);
			validateParsedMap(mapping, result);
			clearModelDef(mapping);
		}
		catch (runtime_error e)
		{
			result.AddError(OP_GENERAL_ERROR, e.what());
		}
	}


#ifdef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping)
	{
		PARSINGRESULT result;
		try
		{
			OpStandaloneFile *file = new OpStandaloneFile(path);
			parseFile(file, mapping, result);
		}
		catch (runtime_error e)
		{
			result.AddError(OP_GENERAL_ERROR, e.what());
		}
		return result;
	}
#else


	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root)
	{
		PARSINGRESULT result;
		try
		{
			OpOrbiterFile *file = new OpOrbiterFile(path, root);
			parseFile(file, mapping, result);
		}
		catch (runtime_error e)
		{
			result.AddError(OP_GENERAL_ERROR, e.what());
		}
		return result;
	}

	PARSINGRESULT ParseFile(FILEHANDLE fileHandle, OpModelDef &mapping)
	{
		PARSINGRESULT result;
		try
		{
			OpOrbiterFile *file = new OpOrbiterFile(fileHandle);
			parseFile(file, mapping, result);
		}
		catch (runtime_error e)
		{
			result.AddError(OP_GENERAL_ERROR, e.what());
		}
		return result;
	}

#endif
}




