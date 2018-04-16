#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "OpValue.h"
#include "OpInt.h"


namespace Oparse
{

	OpInt::OpInt(int & receiver) : OpValue(OP_INT), receiver(receiver)
	{
	}

	OpInt::~OpInt()
	{
	}

	void OpInt::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		try
		{
			receiver = stoi(value);
			setParsed();
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: Unable to convert \"" + value + "\" to int!");
		}
	}
}