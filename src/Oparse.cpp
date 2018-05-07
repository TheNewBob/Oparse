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
	const string OP_GENERAL_ERROR = "OP_GENERAL_ERROR";
	const string DO_NOT_PARSE = "$DO_NOT_PARSE$";


	OpModelDef MergeModelDefs(const OpModelDef & def1, const OpModelDef & def2)
	{
		OpModelDef mergedDef = def1;
		for (auto i = def2.begin(); i != def2.end(); ++i)
		{
			auto mapping = mergedDef.find(i->first);
			if (mapping != mergedDef.end())
			{
				// release allocated parsers and validators from def1 before overwriting them
				delete mapping->second.first;
				auto &validators = mapping->second.second;
				for (unsigned int j = 0; j < validators.size(); ++j)
				{
					delete validators[j];
				}
				// overvrite the value with the one in def2
				mapping->second = i->second;
			}
			else
			{
				// the value is not in def1, making things a lot easier
				mergedDef[i->first] = i->second;
			}
		}
		return mergedDef;
	}


	pair<string, string> splitParamAndValue(const string &configline)
	{
		vector<string> tokens;
		SplitString(configline, tokens, "=");
		string key = RemoveExtraWhiteSpace(tokens[0]);
		string value = tokens.size() > 1 ? RemoveExtraWhiteSpace(tokens[1]) : "";
		return make_pair(StringToLower(key), value);
	}

	void MakeMappingKeysLowerCase(OpModelDef &mapping)
	{
		OpModelDef newMapping;
		for (auto i = mapping.begin(); i != mapping.end(); ++i)
		{
			auto value = i->second;
			auto key = StringToLower(i->first);
			newMapping[key] = value;
		}
		mapping.clear();
		mapping = newMapping;
	}


	OpValue *GetParamFromMapping(const string key, const OpModelDef &mapping)
	{
		auto lowercaseKey = StringToLower(key);
		auto it = mapping.find(lowercaseKey);
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
		
		MakeMappingKeysLowerCase(mapping);

		while (!endOfBlock && file->NextLine(l))
		{
			// remove comments, i.e. everything left of a ;, as well as leading and trailing whitespace
			if (l.find_first_of(';') != std::string::npos)
				l.erase(l.find_first_of(';'), std::string::npos);
			l = RemoveExtraWhiteSpace(l);

			if (l != "")
			{
				string lowercaseLine = StringToLower(l);
				// Check if this is the beginning of a block
				if (lowercaseLine.compare(0, 6, "begin_") == 0 && !StringBeginsWith(blockList, DO_NOT_PARSE))
				{
					if (blockList != "")
					{
						result.AddError(OP_GENERAL_ERROR, "Block nested in BlockList is not allowed: " + l + ", aborting!");
						throw runtime_error("Aborted parsing due to fatal error!");
					}
					string blockname = lowercaseLine.substr(6);
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
						blockList = DO_NOT_PARSE + blockname;
					}
				}
				// Check if this is the end of a block
				else if (lowercaseLine.compare(0, 4, "end_") == 0)
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
						SplitString(lowercaseLine.substr(4), paramTokens, " \t");
						if (paramTokens.size() == 0)
						{
							result.AddError(blockList, "END_ without block specifier!");
						}
						else if (StringBeginsWith(blockList, DO_NOT_PARSE))
						{
							auto beginingOfName = DO_NOT_PARSE.length();
							auto lengthOfName = paramTokens[0].length();
							if (blockList.compare(beginingOfName, lengthOfName, paramTokens[0]) == 0)
							{
								// A block that is not mapped has ended
								blockList = "";
							}
						}
						else if (paramTokens[0] != blockList.substr(0, paramTokens[0].length()))
						{
							result.AddError(blockList, "Unexpected end of block: " + l + ". Expected END_" + blockList + "!");
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
					// If we're inside an unmapped block, don't bother parsing anything.
					if (!StringBeginsWith(blockList, DO_NOT_PARSE))
					{
						if (blockList == "")
						{
							// We're not inside a BlockList.
							auto keyValue = splitParamAndValue(l);
							OpValue *parser = GetParamFromMapping(keyValue.first, mapping);
							if (parser != NULL)
								parser->ParseValue(keyValue.first, keyValue.second, result);
						}
						else
						{
							// Line contains no =, must be an item of a BlockList
							OpValue *parser = GetParamFromMapping(blockList, mapping);
							if (parser != NULL)
								parser->ParseValue(blockList, l, result);
						}
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
			auto type = value->GetType();
			vector<OpValidator*> &validators = param->second.second;

			if (type == OP_MIXEDLIST)
			{
				((OpMixedList*)value)->Validate(param->first, result);
			}
			else if (type == OP_BLOCKLIST)
			{
				((OpBlockListFacade*)value)->Validate(param->first, result);
			}

			for (auto validator = validators.begin(); validator != validators.end(); ++validator)
			{
				auto conditional = dynamic_cast<OpvConditionalRequiredFacade*>(*validator);
				if (conditional != NULL) conditional->Validate(value, param->first, mapping, result);
				else (*validator)->Validate(value, param->first, result);
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

	void writeToFile(OpFile *file, OpModelDef &mapping)
	{
		stringstream result;

		for (auto i = mapping.begin(); i != mapping.end(); ++i)
		{
			i->second.first->Serialize(i->first, result, 0);
		}

		file->WriteStream(result);
	}


#ifdef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping)
	{
		PARSINGRESULT result;
		result.filename = path;
		try
		{
			OpStandaloneFile *file = new OpStandaloneFile(path);
			parseFile(file, mapping, result);
			delete file;
		}
		catch (runtime_error e)
		{
			result.AddError(OP_GENERAL_ERROR, e.what());
		}
		return result;
	}


	void WriteFile(string path, OpModelDef & mapping)
	{
		OpStandaloneFile *file = new OpStandaloneFile(path, true);
		writeToFile(file, mapping);
		delete file;
	}


#else


	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root)
	{
		PARSINGRESULT result;
		result.filename = path;
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

	PARSINGRESULT ParseFile(FILEHANDLE fileHandle, OpModelDef &mapping, string filename)
	{
		PARSINGRESULT result;
		result.filename = filename;
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




