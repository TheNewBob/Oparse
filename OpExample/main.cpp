//#define OPARSE_STANDALONE
#include "OpStdLibs.h"
#include "Oparse.h"
#include "NestedModel.h"
#include "MyModel.h"

using namespace Oparse;

struct MixedListDemo {
	string first = "";
	string second = "";
	string third = "";
	VECTOR3 vector3;
	bool testSuccessful = false;

	OpMixedList *GetMapping()
	{
		return _MixedList(OpValues() =
			{ _String(first),
			  _Vector3(vector3),
			  _String(second),
			  _Bool(testSuccessful),
			  _String(third) }, ",");
	}
};

int main()
{
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
	vector<MixedListDemo*> blockDemo;
	
	MyModel myModel;
	

	vector<string>() = {};
	OpModelDef model = {
		{ "answer",{ _Int(answer),{ _REQUIRED() } } },
		{ "sqrt2",{ _Float(sqrt2),{} } },
		{ "pi",{ _Double(pi),{} } },
		{ "question",{ _String(question),{} } },
		{ "makesSense",{ _Bool(makesSense),{} } },
		{ "vector3", { _Vector3(vector3), {} } },
		{ "isNotHere",{ _Bool(isNotHere),{ _REQUIRED() } } },
		{ "intList", { _List(intList), {} } },
		{ "floatList", { _List(floatList), {} } },
		{ "boolList",{ _List(boolList),{} } },
		{ "stringList",{ _List(stringList, "#"),{} } },
		{ "vector3List", { _List(vector3List), {} } },
		{ "mixedList", { mixedList.GetMapping(), {} } },
		{ "BLOCKLIST 1", { _Block<MixedListDemo>(blockDemo), {} } },
		{ "MODEL 1", { &myModel, {} } }
	};

	auto result = Oparse::ParseFile(
		"testme.cfg",
		model
	);

	bool bugme = true;

}