#include "OpStdLibs.h"
#include "Oparse.h"


void Oparse::OpvConditionalRequiredByParam::Validate(OpValue * value, string paramName, OpModelDef & mapping, PARSINGRESULT & result)
{
	auto i = mapping.find(otherParamName);
	if (i != mapping.end())
	{
		auto otherValue = i->second.first;
		if (exclusive)
		{
			if (otherValue->WasParsed() && value->WasParsed())
				result.AddError(paramName, "Parameter must not be present if parameter " + otherParamName + " is present!");
			else if (!otherValue->WasParsed() && !value->WasParsed())
				result.AddError(paramName, "Parameter is required if parameter " + otherParamName + " is not present!");
		}
		else
		{
			if (otherValue->WasParsed() && !value->WasParsed())
				result.AddError(paramName, "Parameter is required if parameter " + otherParamName + " is present!");
			else if (!otherValue->WasParsed() && value->WasParsed())
				result.AddError(paramName, "Parameter must not be present if parameter " + otherParamName + " is not present!");
		}
	}
	else
	{
		result.AddWarning(paramName, "Mapping for parameter " + otherParamName + " not found for conditional validation. Possibly wrong parameter name or outside of blockscope!");
	}
}



// ConditionalRequiredByParamValue

void Oparse::OpvConditionalRequiredByParamValue::Validate(OpValue * value, string paramName, OpModelDef & mapping, PARSINGRESULT & result)
{
	auto i = mapping.find(otherParamName);
	string otherValueAsString = otherParamValueAsString();
	if (i != mapping.end())
	{
		OpValue *otherParam = i->second.first;
		if (otherParam->GetType() == type)
		{
			if (otherParam->WasParsed())
			{
				bool isMatch = false;
				if (type == OP_STRING)
					isMatch = *((string*)otherParamValue) == StringToLower(*((string*)otherParam->GetValue()));
				else if (type == OP_INT)
					isMatch = *((int*)otherParamValue) == *((int*)otherParam->GetValue());
				else if (type == OP_BOOL)
					isMatch = *((bool*)otherParamValue) == *((bool*)otherParam->GetValue());

				if (isMatch && !value->WasParsed())
				{
					stringstream msg;
					msg << "Parameter is required if parameter " << otherParamName << " has value " << otherValueAsString << "!";
					result.AddError(paramName, msg.str());
				}
				else if (!isMatch && value->WasParsed())
				{
					stringstream msg;
					msg << "Parameter must not be present if parameter " << otherParamName << " does not have value " << otherValueAsString << "!";
					result.AddError(paramName, msg.str());
				}
			}
			else if (value->WasParsed())
			{
				stringstream msg;
				msg << "Parameter must not be present if parameter " << otherParamName << " does not have value " << otherValueAsString << "!";
				result.AddError(paramName, msg.str());
			}
		}
		else
		{
			stringstream msg;
			msg << "Type mismatch: parameter " << otherParamName << " is not of appropriate type for expected value " << otherValueAsString << "!";
			result.AddWarning(paramName, msg.str());
		}
	}
	else
	{
		result.AddWarning(paramName, "Mapping for parameter " + otherParamName + " not found for conditional validation. Possibly wrong parameter name or outside of blockscope!");
	}
}

string Oparse::OpvConditionalRequiredByParamValue::otherParamValueAsString()
{
	stringstream ss;
	if (type == OP_STRING) ss << *((string*)otherParamValue);
	else if (type == OP_INT) ss << *((int*)otherParamValue);
	else if (type == OP_BOOL) ss << *((int*)otherParamValue);
	return ss.str();
}

