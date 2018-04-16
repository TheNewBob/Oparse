#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "StringOps.h"
#include "OpValue.h"
#include "OpVector3.h"

namespace Oparse
{
	OpVector3::OpVector3(VECTOR3 & receiver): OpValue(OP_VECTOR3), receiver(receiver)
	{
	}

	void OpVector3::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		try
		{
			vector<string> elements;
			SplitString(value, elements, " ");
			if (elements.size() != 3)
			{
				result.AddError(key, "VECTOR3 cannot have more or less than 3 elements!");
			}
			else
			{
				receiver.x = stod(elements[0]);
				receiver.y = stod(elements[1]);
				receiver.z = stod(elements[2]);
			}
		}
		catch (exception)
		{
			result.AddError(key, "Type mismatch: Unable to convert \"" + value + "\" to VECTOR3!");
		}
	}
}