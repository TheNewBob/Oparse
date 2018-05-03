#pragma once


namespace Oparse
{
	/**
	 * \brief A parameter that takes a lambda function to parse a value.
	 * The lambda receives the value as a string, and expects an error string in return. A non-empty string 
	 * received from the lambda will be added to the errors for this parameter.
	 */
	class OpLambda
		: public OpValue
	{
	public:
		OpLambda(function<string(string value)> lambda, bool tolower = false) : OpValue(OP_LAMBDA), lambda(lambda), tolower(tolower) {};

		void ParseValue(string key, string value, PARSINGRESULT &result)
		{
			string error = "";
			if (tolower) error = lambda(StringToLower(RemoveExtraWhiteSpace(value)));
			else error = lambda(RemoveExtraWhiteSpace(value));

			if (error != "") result.AddError(key, error);
		}

		void *GetValue() { return NULL; };
	private:
		function<string(string value)> lambda = NULL;
		bool tolower;
	};

}