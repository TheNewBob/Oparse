#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "OpValue.h"
#include "OpDouble.h"


namespace Oparse
{


	OpDouble::OpDouble(double & receiver) : receiver(receiver)
	{
	}

	OpDouble::~OpDouble()
	{
	}

	void OpDouble::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		try
		{
			receiver = stod(value);
			setParsed();
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: Unable to convert \"" + value + "\" to double!");
		}
	}
}