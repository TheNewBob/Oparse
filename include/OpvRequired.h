#pragma once

namespace Oparse
{
	class OpvRequired
		: public OpValidator
	{
	public:
		OpvRequired();
		~OpvRequired();

		void Validate(OpValue *value, const string paramName, PARSINGRESULT &result);
	};

}