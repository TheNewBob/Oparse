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

	OpVector3 * _Vector3(VECTOR3 & receiver)
	{
		return new OpVector3(receiver);
	}

	OpList *_List(vector<int>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<float>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<double>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<bool>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<string>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpList *_List(vector<VECTOR3>& receiver, string delimiter)
	{
		return new OpList(receiver, delimiter);
	}

	OpMixedList * _MixedList(OpValues receivers, string delimiter)
	{
		return new OpMixedList(receivers, delimiter);
	}

	//validators

	OpvRequired *_REQUIRED()
	{
		return new OpvRequired();
	}
}