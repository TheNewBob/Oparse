#pragma once

namespace Oparse
{
	class OpNumericValidator
		: public OpValidator
	{
	public:

		OpNumericValidator(function<bool(double value)> predicate, string errormsg) : predicate(predicate), errormsg(errormsg) {};

		void Validate(OpValue *value, const string paramName, PARSINGRESULT &result);

	private:

		bool isApplicableTo(OpValue *value);


		template <typename T> bool validateVector(void *value)
		{
			vector<T> list = *((vector<T>*)value);
			for (unsigned int i = 0; i < list.size(); ++i)
			{
				if (!predicate(list[i])) return false;
			}
			return true;
		};


		function<bool(double value)> predicate;
		string errormsg;
	};
}