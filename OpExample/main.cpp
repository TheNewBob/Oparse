//#define OPARSE_STANDALONE
#include "OpStdLibs.h"
#include "Oparse.h"

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

	

	vector<string>() = {};
	OpModelDef model = {
		{ "answer",{ _Int(answer),{ _REQUIRED() } } },
		{ "sqrt2",{ _Float(sqrt2),{} } },
		{ "pi",{ _Double(pi),{} } },
		{ "question",{ _String(question),{} } },
		{ "makesSense",{ _Bool(makesSense),{} } },
		{ "vector3", { _Vector3(vector3), {} } },
		{ "isNotHere",{ _Bool(isNotHere),{ _REQUIRED() } } },
		{ "intList", { _LIST(intList), {} } },
		{ "floatList", { _LIST(floatList), {} } },
		{ "boolList",{ _LIST(boolList),{} } },
		{ "stringList",{ _LIST(stringList, "#"),{} } },
		{ "vector3List", { _LIST(vector3List), {} } },
		{ "mixedList", { mixedList.GetMapping(), {} } },
		{ "BLOCKLIST 1", { _Block<MixedListDemo>(blockDemo), {} } }
	};

	auto result = Oparse::ParseFile(
		"testme.cfg",
		model
	);

	bool bugme = true;

}