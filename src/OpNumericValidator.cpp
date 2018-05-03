#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "OParse.h"

namespace Oparse
{

	void Oparse::OpNumericValidator::Validate(OpValue * value, const string paramName, PARSINGRESULT & result)
	{
		if (!value->WasParsed()) return;

		bool validationFailed = false;
		OP_TYPE type = value->GetType();
		void *val = value->GetValue();

		if (isApplicableTo(value))
		{
			if (type == OP_LIST)
			{
				auto listType = ((OpList*)value)->GetListType();
				if (listType == OP_INT)
					validationFailed = !validateVector<int>(val);
				else if (listType == OP_FLOAT)
					validationFailed = !validateVector<float>(val);
				else if (listType == OP_DOUBLE)
					validationFailed = !validateVector<double>(val);
			}
			else
			{
				validationFailed = !predicate((*(double*)val));
			}
		}
		else
		{
			result.AddWarning(paramName, "Numeric Validator is not applicable to " + OpValue::GetTypeDescriptionFor(type));
		}

		if (validationFailed)
		{
			stringstream ss;
			ss << errormsg << ", instead is " << *(double*)val << "!";
			result.AddError(paramName, ss.str());
		}
	}

	bool Oparse::OpNumericValidator::isApplicableTo(OpValue * value)
	{
		auto type = value->GetType();

		if (type == OP_LIST)
		{
			type = ((OpList*)value)->GetListType();
		}

		switch (type)
		{
		case OP_INT:
		case OP_FLOAT:
		case OP_DOUBLE: return true;
		default: return false;
		}
	}
}