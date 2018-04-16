#include "OpStdLibs.h"
#include "Oparse.h"

void Oparse::OpvLength::Validate(OpValue * value, const string paramName, PARSINGRESULT & result)
{
	if (!value->WasParsed()) return;

	OP_TYPE type = value->GetType();

	if (isApplicableTo(value))
	{
		if (type == OP_STRING)
		{
			string *val = (string*)value->GetValue();
			if (val->length() < min || val->length() > max)
			{
				stringstream ss;
				ss << "String must be between " << min << " and " << max << " characters long!";
				result.AddError(paramName, ss.str());
			}
		}
		else if (type == OP_LIST)
		{
			auto list = (OpList*)value;
			if (list->GetSize() < min || list->GetSize() > max)
			{
				stringstream ss;
				ss << "List must be between " << min << " and " << max << " elements long!";
				result.AddError(paramName, ss.str());
			}
		}
	}
	else
	{
		result.AddWarning(paramName, "Validator length is not applicable to type " + OpValue::GetTypeDescriptionFor(type) + "!");
	}

}

bool Oparse::OpvLength::isApplicableTo(OpValue * value)
{
	auto type = value->GetType();
	switch (type)
	{
	case OP_STRING: 
	case OP_LIST: return true;
	default: return false;
	}
}
