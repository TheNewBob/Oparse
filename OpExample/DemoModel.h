#pragma once

struct MixedListDemo {
	string first = "";
	string second = "";
	string third = "";
	VECTOR3 vector3;
	bool testSuccessful = false;

	Oparse::OpMixedList *GetMapping();
};


class DemoModel
{
public:
	int answer = -1;
	float sqrt2 = -1;
	double pi = -1;
	string question = "";
	bool makesSense = true;
	bool isNotHere = true;
	VECTOR3 vector3;

	vector<int> intList;
	vector<double> floatList;
	vector<bool> boolList;
	vector<string> stringList;
	vector<VECTOR3> vector3List;

	MixedListDemo mixedList;
	vector<MixedListDemo> blockDemo;

	MyModel myModel;

	OpModelDef GetModelDef();


};