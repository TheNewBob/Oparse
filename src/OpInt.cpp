#include "OpStdLibs.h"
#include "OpValue.h"
#include "OpInt.h"


namespace Oparse
{

	OpInt::OpInt(int & receiver) : receiver(receiver)
	{
	}

	OpInt::~OpInt()
	{
	}

	void OpInt::ParseValue(string value)
	{
		receiver = stoi(value);
		setParsed();
	}
}