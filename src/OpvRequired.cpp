#include "OpStdLibs.h"
#include "Oparse.h"


namespace Oparse
{
	OpvRequired::OpvRequired()
	{
	}


	OpvRequired::~OpvRequired()
	{
	}

	void OpvRequired::Validate(OpValue * value, const string paramName, PARSINGRESULT & result)
	{
		if (!value->WasParsed())
		{
			result.AddError(paramName, "Parameter is required!");
		}
	}
}