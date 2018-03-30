#pragma once
namespace Oparse
{

	class OpValidator
	{
	public:
		OpValidator() {};
		~OpValidator() {};
		
		virtual void Validate(OpValue *value, const string paramName, PARSINGRESULT &result) = 0;
	};

}