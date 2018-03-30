#include "OpStdLibs.h"
#include "OpValue.h"
#include "OpFloat.h"


namespace Oparse
{

	OpFloat::OpFloat(float & receiver) : receiver(receiver)
	{
	}

	OpFloat::~OpFloat()
	{
	}

	void OpFloat::ParseValue(string value)
	{
		receiver = stof(value);
		setParsed();
	}
}