#include "OpStdLibs.h"
#include "StringOps.h"
#include "OpValue.h"
#include "OpString.h"

namespace Oparse
{
	OpString::OpString(string &receiver, bool toLower) : receiver(receiver), toLower(toLower)
	{
	}

	OpString::~OpString()
	{
	}

	void OpString::ParseValue(string value)
	{
		if (toLower)
		{
			receiver = Oparse::StringToLower(value);
		}
		else
		{
			receiver = value;
		}
		setParsed();
	}
}