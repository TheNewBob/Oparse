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
			if (val->length() < minimum || val->length() > maximum)
			{
				stringstream ss;
				ss << "String is \"" + *val + "\" but must be between " << minimum << " and " << maximum << " characters long!";
				result.AddError(paramName, ss.str());
			}
		}
		else if (type == OP_LIST)
		{
			auto list = (OpList*)value;
			if (list->GetSize() < minimum || list->GetSize() > maximum)
			{
				stringstream ss;
				ss << "List must be between " << minimum << " and " << maximum << " elements long!";
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
