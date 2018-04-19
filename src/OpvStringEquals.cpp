#include "OpStdLibs.h"
#include "Oparse.h"

Oparse::OpvStringEquals::OpvStringEquals(vector<string> allowedValues, bool caseSensitive) : allowedValues(allowedValues), caseSensitive(caseSensitive)
{

}

void Oparse::OpvStringEquals::Validate(OpValue * value, const string paramName, PARSINGRESULT & result)
{
	if (value->WasParsed())
	{
		if (isApplicableTo(value))
		{
			string *str = (string*)value->GetValue();
			string toValidate = *str;
			if (!caseSensitive)
			{
				toValidate = StringToLower(toValidate);
			}

			bool isValid = false;
			for (unsigned int i = 0; i < allowedValues.size(); ++i)
			{
				string allowedValue = allowedValues[i];
				if (!caseSensitive)
				{
					allowedValue = StringToLower(allowedValue);
				}
				if (allowedValue.compare(toValidate) == 0)
				{
					isValid = true;
					break;
				}
			}

			if (!isValid)
			{
				string msg = "String is \"" + *str + "\" but must match any of these values: ";
				for (unsigned int i = 0; i < allowedValues.size(); ++i)
				{
					msg += allowedValues[i];
					if (i < allowedValues.size() - 1)
					{
						msg += ", ";
					}
				}
				result.AddError(paramName, msg);
			}
		}
		else
		{
			result.AddWarning(paramName, "Validator StringEquals is not applicable to type " + OpValue::GetTypeDescriptionFor(value->GetType()) + "!");
		}
	}
}

bool Oparse::OpvStringEquals::isApplicableTo(OpValue * value)
{
	if (value->GetType() == OP_STRING) return true;
	else return false;
}
