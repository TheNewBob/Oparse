//#define OPARSE_STANDALONE
#include "OpStdLibs.h"
#include "Oparse.h"

using namespace Oparse;

int main()
{
	int answer = -1;
	float sqrt2 = -1;
	double pi = -1;
	string question = "";
	bool makesSense = true;
	bool isNotHere = true;
	vector<int> intList;
	vector<double> floatList;
	vector<bool> boolList;
	vector<string> stringList;
	
	

	vector<string>() = {};
	OpModelDef model = {
		{ "answer",{ Oparse::_Int(answer),{ _REQUIRED() } } },
		{ "sqrt2",{ Oparse::_Float(sqrt2),{} } },
		{ "pi",{ Oparse::_Double(pi),{} } },
		{ "question",{ Oparse::_String(question),{} } },
		{ "makesSense",{ Oparse::_Bool(makesSense),{} } },
		{ "isNotHere",{ _Bool(isNotHere),{ _REQUIRED() } } },
		{ "intList", { _LIST(intList), {} } },
		{ "floatList", { _LIST(floatList), {} } },
		{ "boolList",{ _LIST(boolList),{} } },
		{ "stringList",{ _LIST(stringList, "#"),{} } }
	};

	auto result = Oparse::ParseFile(
		"testme.cfg",
		model
	);

	bool bugme = true;

}