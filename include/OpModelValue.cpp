#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
#include "OpValue.h"
#include "OpValidator.h"
#include "OpModel.h"
#include "OpModelValue.h"


namespace Oparse
{

	void Oparse::OpModelValue::ParseValue(string value)
	{
		throw runtime_error("ParseValue() should never be called on OpModel!"); 
	}

	OpModelDef &OpModelValue::GetModelDef()
	{
		return modelDef;
	}

}