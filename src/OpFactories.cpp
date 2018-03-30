#include "OpStdLibs.h"
#include "Oparse.h"

// validators
Oparse::OpvRequired Oparse::REQUIRED;

namespace Oparse
{

	OpInt *_Int(int & receiver)
	{
		return new OpInt(receiver);
	}

	OpFloat *_Float(float & receiver)
	{
		return new OpFloat(receiver);
	}

	OpDouble *_Double(double & receiver)
	{
		return new OpDouble(receiver);
	}

	OpString *_String(string & receiver)
	{
		return new OpString(receiver);
	}

	OpBool * _Bool(bool & receiver)
	{
		return new OpBool(receiver);
	}
}