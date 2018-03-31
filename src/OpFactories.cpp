#include "OpStdLibs.h"
#include "Oparse.h"


namespace Oparse
{
	// types
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

	OpList *_LIST(vector<int>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_LIST(vector<float>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_LIST(vector<double>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_LIST(vector<bool>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_LIST(vector<string>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}


	//validators

	OpvRequired *_REQUIRED()
	{
		return new OpvRequired();
	}
}