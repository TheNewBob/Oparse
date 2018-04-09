#pragma once

using namespace Oparse;
using namespace std;

class NestedModel
{

public:
	NestedModel() {};
	~NestedModel() {};

	string param1 = "";
	int param2 = 0;
	vector<VECTOR3> param3;
	int param4 = 0;

	OpModelDef GetModelDef()
	{
		return 	OpModelDef() = {
			{ "param1",	{ _String(param1),	{} } },
			{ "param2",	{ _Int(param2),		{} } },
			{ "param3",	{ _List(param3),	{} } },
			{ "param4", { _Int(param4),		{_REQUIRED()} } }
		};
	};
};

