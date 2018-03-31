#include "OpStdLibs.h"
#include "StringOps.h"
#include "OpValue.h"
#include "OpVector3.h"

namespace Oparse
{
	OpVector3::OpVector3(VECTOR3 & receiver): receiver(receiver)
	{
	}

	void OpVector3::ParseValue(string value)
	{
		vector<string> elements;
		SplitString(value, elements, " ");
		if (elements.size() != 3) throw runtime_error("VECTOR3 cannot have more or less than 3 elements!");
		receiver.x = stod(elements[0]);
		receiver.y = stod(elements[1]);
		receiver.z = stod(elements[2]);
	}
}