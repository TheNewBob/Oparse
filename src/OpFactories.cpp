#include "OpStdLibs.h"
#include "Oparse.h"


namespace Oparse
{
	// types
	OpInt *_Param(int & receiver)
	{
		return new OpInt(receiver);
	}

	OpFloat *_Param(float & receiver)
	{
		return new OpFloat(receiver);
	}

	OpDouble *_Param(double & receiver)
	{
		return new OpDouble(receiver);
	}

	OpString *_Param(string & receiver)
	{
		return new OpString(receiver);
	}

	OpBool * _Param(bool & receiver)
	{
		return new OpBool(receiver);
	}

	OpVector3 * _Param(VECTOR3 & receiver)
	{
		return new OpVector3(receiver);
	}

	OpLambda * _Param(function<string(string value)> lambda, bool tolower)
	{
		return new OpLambda(lambda, tolower);
	}

	OpList *_List(vector<int>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<float>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<double>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<bool>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<string>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<VECTOR3>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpMixedList * _MixedList(OpValues receivers, string delimiter)
	{
		return new OpMixedList(receivers, delimiter);
	}

	//validators

	OpvRequired *_REQUIRED()
	{
		return new OpvRequired();
	}

	OpvConditionalRequiredByParam * _REQUIREDBY(string paramName)
	{
		return new OpvConditionalRequiredByParam(false, paramName);
	}

	OpvConditionalRequiredByParamValue *_REQUIREDBY(string paramName, int value)
	{
		return new OpvConditionalRequiredByParamValue(paramName, value);
	}

	OpvConditionalRequiredByParamValue *_REQUIREDBY(string paramName, bool value)
	{
		return new OpvConditionalRequiredByParamValue(paramName, value);
	}

	OpvConditionalRequiredByParamValue *_REQUIREDBY(string paramName, string value)
	{
		return new OpvConditionalRequiredByParamValue(paramName, value);
	}

	OpvConditionalRequiredByParam * _EXCLUDEDBY(string paramName)
	{
		return new OpvConditionalRequiredByParam(true, paramName);
	}

	OpNumericValidator * _MAX(double max)
	{
		stringstream ss;
		ss << "Value must not be larger than " << max;
		return new OpNumericValidator(
			[max](double value) { return value <= max; },
			ss.str());
	}

	OpNumericValidator * _MIN(double min)
	{
		stringstream ss;
		ss << "Value must not be smaller than " << min;
		return new OpNumericValidator([min](double value) { return value >= min; },
			ss.str());
	}

	OpNumericValidator * _RANGE(double min, double max)
	{
		stringstream ss;
		ss << "Value must be between " << min << " and " << max;
		return new OpNumericValidator([min, max](double value) { return value >= min && value <= max; },
			ss.str());
	}

	OpvLength * _LENGTH(unsigned int max)
	{
		return new OpvLength(0, max);
	}

	OpvLength * _LENGTH(unsigned int min, unsigned int max)
	{
		if (min > max) throw runtime_error("min cannot be larger than max!");
		return new OpvLength(min, max);
	}

	OpvStringEquals * _ISANYOF(vector<string> allowedValues, bool caseSensitive)
	{
		return new OpvStringEquals(allowedValues, caseSensitive);
	}
}