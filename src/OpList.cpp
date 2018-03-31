#include "OpStdLibs.h"
#include "OpValue.h"
#include "OpInt.h"
#include "OpFloat.h"
#include "OpDouble.h"
#include "OpString.h"
#include "OpBool.h"
#include "OpList.h"
#include "StringOps.h"

namespace Oparse
{

	enum LISTTYPE
	{
		INT,
		FLOAT,
		DOUBLE,
		BOOL,
		STRING,
		VECTOR3
	};

	OpList::OpList(vector<int> &receiver, string delimiter)
		: receiver(&receiver), 
		delimiter(delimiter), 
		type(INT)
	{
	}

	OpList::OpList(vector<float> &receiver, string delimiter) 
		: receiver(&receiver), 
		delimiter(delimiter),
		type(FLOAT)
	{
	}

	OpList::OpList(vector<double> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(DOUBLE)
	{}

	OpList::OpList(vector<bool> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(BOOL)
	{}

	OpList::OpList(vector<string> &receiver, string delimiter)
		: receiver(&receiver),
		delimiter(delimiter),
		type(STRING)
	{}

	void OpList::ParseValue(string value)
	{
		vector<string> elements;
		SplitString(value, elements, delimiter);
		
		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			if (type == INT)
			{
				int temp = -1;
				OpInt parser(temp);
				parser.ParseValue(elements[i]);
				((vector<int>*)receiver)->push_back(temp);
			}
			else if (type == FLOAT)
			{
				float temp = -1;
				OpFloat parser(temp);
				parser.ParseValue(elements[i]);
				((vector<float>*)receiver)->push_back(temp);
			}
			else if (type == DOUBLE)
			{
				double temp = -1;
				OpDouble parser(temp);
				parser.ParseValue(elements[i]);
				((vector<double>*)receiver)->push_back(temp);
			}
			else if (type == BOOL)
			{
				bool temp = false;
				OpBool parser(temp);
				parser.ParseValue(elements[i]);
				((vector<bool>*)receiver)->push_back(temp);
			}
			else if (type == STRING)
			{
				string temp = "";
				OpString parser(temp);
				parser.ParseValue(elements[i]);
				((vector<string>*)receiver)->push_back(temp);
			}
			else throw runtime_error("Error while parsing OpList: Unsupported type!");
		}
	}
}



