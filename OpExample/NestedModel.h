#pragma once

using namespace Oparse;
using namespace std;

class NestedModel
	: public OpModel
{

public:
	NestedModel() : OpModel(
		OpModelDef() = {
			{ "param1",{ _String(param1),{} } },
			{ "param2",{ _Int(param2),{} } },
			{ "param3",{ _List(param3),{} } }
		}) {};

		~NestedModel() {};

		string param1 = "";
		int param2 = 0;
		vector<VECTOR3> param3;
};

