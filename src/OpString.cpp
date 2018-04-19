#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "StringOps.h"
#include "OpValue.h"
#include "OpString.h"

namespace Oparse
{
	OpString::OpString(string &receiver, bool toLower) : OpValue(OP_STRING), receiver(receiver), toLower(toLower)
	{
	}

	OpString::~OpString()
	{
	}

	void OpString::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		try
		{
			if (toLower)
			{
				receiver = RemoveExtraWhiteSpace(StringToLower(value));
			}
			else
			{
				receiver = RemoveExtraWhiteSpace(value);
			}
			setParsed();
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: Unable to convert \"" + value + "\" to string!");
		}
	}
}