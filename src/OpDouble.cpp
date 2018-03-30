#include "OpStdLibs.h"
#include "OpValue.h"
#include "OpDouble.h"


namespace Oparse
{

	void OpDouble::ParseValue(string value)
	{
		receiver = stod(value);
		setParsed();
	}

	OpDouble::OpDouble(double & receiver) : receiver(receiver)
	{
	}

	OpDouble::~OpDouble()
	{
	}

}