#pragma once

using namespace Oparse;
using namespace std;

class MyModel
	: public OpModel
{

public:
	MyModel() : OpModel(
		OpModelDef() = {
			{ "blockParam1",{ _Double(blockParam1),{} } },
			{ "blockParam2",{ _String(blockParam2),{} } },
			{ "blockParam3",{ _List(blockParam3),{} } }
		}) {};

		~MyModel() {};

	double blockParam1 = 0;
	string blockParam2 = "";
	vector<int> blockParam3;
};

