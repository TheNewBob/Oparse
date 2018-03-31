#include "OpStdLibs.h"
#include "OpValue.h"
#include "OpInt.h"
#include "OpFloat.h"
#include "OpDouble.h"
#include "OpString.h"
#include "OpBool.h"
#include "OpVector3.h"
#include "OpList.h"
#include "StringOps.h"

namespace Oparse
{

	enum LISTTYPE
	{
		T_INT,
		T_FLOAT,
		T_DOUBLE,
		T_BOOL,
		T_STRING,
		T_VECTOR3
	};

	OpList::OpList(vector<int> &receiver, string delimiter)
		: receiver(&receiver), 
		delimiter(delimiter), 
		type(T_INT)
	{
	}

	OpList::OpList(vector<float> &receiver, string delimiter) 
		: receiver(&receiver), 
		delimiter(delimiter),
		type(T_FLOAT)
	{
	}

	OpList::OpList(vector<double> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(T_DOUBLE)
	{}

	OpList::OpList(vector<bool> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(T_BOOL)
	{}

	OpList::OpList(vector<string> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(T_STRING)
	{}

	OpList::OpList(vector<VECTOR3> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(T_VECTOR3)
	{}

	void OpList::ParseValue(string value)
	{
		vector<string> elements;
		SplitString(value, elements, delimiter);
		
		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			if (type == T_INT)
			{
				int temp = -1;
				OpInt parser(temp);
				parser.ParseValue(elements[i]);
				((vector<int>*)receiver)->push_back(temp);
			}
			else if (type == T_FLOAT)
			{
				float temp = -1;
				OpFloat parser(temp);
				parser.ParseValue(elements[i]);
				((vector<float>*)receiver)->push_back(temp);
			}
			else if (type == T_DOUBLE)
			{
				double temp = -1;
				OpDouble parser(temp);
				parser.ParseValue(elements[i]);
				((vector<double>*)receiver)->push_back(temp);
			}
			else if (type == T_BOOL)
			{
				bool temp = false;
				OpBool parser(temp);
				parser.ParseValue(elements[i]);
				((vector<bool>*)receiver)->push_back(temp);
			}
			else if (type == T_STRING)
			{
				string temp = "";
				OpString parser(temp);
				parser.ParseValue(elements[i]);
				((vector<string>*)receiver)->push_back(temp);
			}
			else if (type == T_VECTOR3)
			{
				VECTOR3 temp;
				OpVector3 parser(temp);
				parser.ParseValue(elements[i]);
				((vector<VECTOR3>*)receiver)->push_back(temp);
			}
			else throw runtime_error("Error while parsing OpList: Unsupported type!");
		}
	}
}



