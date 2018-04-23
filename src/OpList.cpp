#include "OpStdLibs.h"
#include "PARSINGRESULT.h"
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

	OpList::OpList(vector<int> &receiver, string delimiter)
		: OpValue(OP_LIST), receiver(&receiver), 
		delimiter(delimiter), 
		listType(OP_INT)
	{
	}

	OpList::OpList(vector<float> &receiver, string delimiter) 
		: OpValue(OP_LIST), receiver(&receiver),
		delimiter(delimiter),
		listType(OP_FLOAT)
	{
	}

	OpList::OpList(vector<double> &receiver, string delimiter)
		: OpValue(OP_LIST), receiver(&receiver),
		delimiter(delimiter),
		listType(OP_DOUBLE)
	{}

	OpList::OpList(vector<bool> &receiver, string delimiter)
		: OpValue(OP_LIST), receiver(&receiver),
		delimiter(delimiter),
		listType(OP_BOOL)
	{}

	OpList::OpList(vector<string> &receiver, string delimiter)
		: OpValue(OP_LIST), receiver(&receiver),
		delimiter(delimiter),
		listType(OP_STRING)
	{}

	OpList::OpList(vector<VECTOR3> &receiver, string delimiter)
		: OpValue(OP_LIST), receiver(&receiver),
		delimiter(delimiter),
		listType(OP_VECTOR3)
	{}

	void OpList::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		vector<string> elements;
		SplitString(value, elements, delimiter);
		
		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			if (listType == OP_INT)
			{
				int temp = -1;
				OpInt parser(temp);
				parser.ParseValue(key, elements[i], result);
				auto rec = ((vector<int>*)receiver);
				if (!WasParsed()) rec->clear();
				rec->push_back(temp);
				size++;
			}
			else if (listType == OP_FLOAT)
			{
				float temp = -1;
				OpFloat parser(temp);
				parser.ParseValue(key, elements[i], result);
				auto rec = ((vector<float>*)receiver);
				if (!WasParsed()) rec->clear();
				rec->push_back(temp);
				size++;
			}
			else if (listType == OP_DOUBLE)
			{
				double temp = -1;
				OpDouble parser(temp);
				parser.ParseValue(key, elements[i], result);
				auto rec = ((vector<double>*)receiver);
				if (!WasParsed()) rec->clear();
				rec->push_back(temp);
				size++;
			}
			else if (listType == OP_BOOL)
			{
				bool temp = false;
				OpBool parser(temp);
				parser.ParseValue(key, elements[i], result);
				auto rec = ((vector<bool>*)receiver);
				if (!WasParsed()) rec->clear();
				rec->push_back(temp);
				size++;
			}
			else if (listType == OP_STRING)
			{
				string temp = "";
				OpString parser(temp);
				parser.ParseValue(key, elements[i], result);
				auto rec = ((vector<string>*)receiver);
				if (!WasParsed()) rec->clear();
				rec->push_back(temp);
				size++;
			}
			else if (listType == OP_VECTOR3)
			{
				VECTOR3 temp;
				OpVector3 parser(temp);
				parser.ParseValue(key, elements[i], result);
				auto rec = ((vector<VECTOR3>*)receiver);
				if (!WasParsed()) rec->clear();
				rec->push_back(temp);
				size++;
			}
			else
			{
				result.AddError(key, "Error while parsing OpList: Unsupported type!");
			}
			setParsed();

		}
	}
}



