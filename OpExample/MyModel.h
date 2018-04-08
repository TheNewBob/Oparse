#pragma once

using namespace Oparse;
using namespace std;

class MyModel
	: public OpModel
{

public:
	MyModel() : OpModel(
		OpModelDef() = {
			{ "param1",{ _Double(param1),{} } },
			{ "param2",{ _Bool(param2),{} } },
			{ "param3",{ _List(param3),{} } },
			{ "NESTED MODEL 1", { &nestedModel, {} } }
		}) {};

	~MyModel() {};

	double param1 = 0;
	bool param2 = false;
	vector<int> param3;
	NestedModel nestedModel;
};

