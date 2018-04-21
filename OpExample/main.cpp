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
			{
				{ _Param(first), {_ISANYOF(vector<string>() = {"a vector3"}) } },
				{ _Param(vector3), {} },
				{ _Param(second), { _ISANYOF(vector<string>() = { "a vector3" }) } },
				{ _Param(testSuccessful), {} },
				{ _Param(third), { _LENGTH(0, 256)} }
			}, ",");
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
	vector<MixedListDemo> blockDemo;
	
	MyModel myModel;
	

	vector<string>() = {};
	OpModelDef model = {
		{ "answer",{ _Param(answer),{ _REQUIRED() } } },
		{ "sqrt2",{ _Param(sqrt2),{} } },
		{ "pi",{ _Param(pi), {_MAX(3.5)} } },
		{ "question",{ _Param(question), {} } },
		{ "makesSense",{ _Param(makesSense),{} } },
		{ "vector3", { _Param(vector3), {} } },
		{ "isNotHere",{ _Param(isNotHere),{ _REQUIRED() } } },
		{ "intList", { _List(intList), {_MAX(2)} } },
		{ "floatList", { _List(floatList), {} } },
		{ "boolList",{ _List(boolList),{} } },
		{ "stringList",{ _List(stringList, "#"),{} } },
		{ "vector3List", { _List(vector3List), {} } },
		{ "mixedList", { mixedList.GetMapping(), {} } },
		{ "BLOCKLIST 1", { _Block<MixedListDemo>(blockDemo), {} } },
		{ "MODEL 1", { _Model<MyModel>(myModel), {} } }
	};

	auto result = Oparse::ParseFile(
		"testme.cfg",
		model
	);

	bool bugme = true;

}