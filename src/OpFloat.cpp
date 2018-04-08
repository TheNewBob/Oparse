#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "OpValue.h"
#include "OpFloat.h"


namespace Oparse
{

	OpFloat::OpFloat(float & receiver) : receiver(receiver)
	{
	}

	OpFloat::~OpFloat()
	{
	}

	void OpFloat::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		try
		{
			receiver = stof(value);
			setParsed();
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: Unable to convert \"" + value + "\" to float!");
		}
	}
}