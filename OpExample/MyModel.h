#pragma once

using namespace Oparse;
using namespace std;

class MyModel
{

public:
	MyModel() {};
	~MyModel() {};

	double param1 = 0;
	bool param2 = false;
	vector<int> param3;
	NestedModel nestedModel;

	OpModelDef GetModelDef() {
		return OpModelDef() = {
			{ "param1",{ _Param(param1), {} } },
			{ "param2",{ _Param(param2), {} } },
			{ "param3",{ _List(param3), {} } },
			{ "NESTED MODEL 1",{ _Model<NestedModel>(nestedModel), {} } }
		};
	};
};

