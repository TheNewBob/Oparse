#pragma once
namespace Oparse
{

	class OpValidator
	{
	public:
		OpValidator() {};
		virtual ~OpValidator() {};
		
		virtual void Validate(OpValue *value, const string paramName, PARSINGRESULT &result) = 0;



	protected:
		virtual bool isApplicableTo(OpValue *value) = 0;
	};

}