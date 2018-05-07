#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "OpValue.h"
#include "OpBool.h"
#include "StringOps.h"


namespace Oparse
{
	OpBool::OpBool(bool &receiver): OpValue(OP_BOOL), receiver(receiver)
	{
	}


	OpBool::~OpBool()
	{
	}

	void OpBool::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		try
		{
			auto lowercase = StringToLower(RemoveExtraWhiteSpace(value));
			if (lowercase == "true") receiver = true;
			else if (lowercase == "false") receiver = false;
			else if (stoi(value) > 0) receiver = true;
			else receiver = false;
			setParsed();
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: unable to convert \"" + value + "\" to bool!");
		}
	}

	string OpBool::ValueAsString()
	{
		return to_string(receiver);
	}
}