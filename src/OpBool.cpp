#include "OpStdLibs.h"
#include "OpValue.h"
#include "OpBool.h"
#include "StringOps.h"


namespace Oparse
{
	OpBool::OpBool(bool &receiver): receiver(receiver)
	{
	}


	OpBool::~OpBool()
	{
	}
	void OpBool::ParseValue(string value)
	{
		auto lowercase = StringToLower(value);
		if (lowercase == "true") receiver = true;
		else if (lowercase == "false") receiver = false;
		else if (stoi(value) > 0) receiver = true;
		else receiver = false;
		setParsed();
	}
}