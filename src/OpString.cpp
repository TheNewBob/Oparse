#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "StringOps.h"
#include "OpValue.h"
#include "OpString.h"

namespace Oparse
{
	OpString::OpString(string &receiver, bool toLower) : receiver(receiver), toLower(toLower)
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
				receiver = Oparse::StringToLower(value);
			}
			else
			{
				receiver = value;
			}
			setParsed();
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: Unable to convert \"" + value + "\" to string!");
		}
	}
}