#include "OpStdLibs.h"
#include "Oparse.h"
#include "NestedModel.h"
#include "MyModel.h"
#include "DemoModel.h"

using namespace Oparse;

OpModelDef DemoModel::GetModelDef()
{
	return OpModelDef() = {
		{ "test",{ _Param(pi),{} } },
		{ "answer",{ _Param(answer),{ _REQUIRED() } } },
		{ "sqrt2",{ _Param(sqrt2),{} } },
		{ "pi",{ _Param(pi),{ _MAX(3.5), _MIN(0.0) } } },
		{ "question",{ _Param(question),{} } },
		{ "makesSense",{ _Param(makesSense),{ _REQUIREDBY("answer", 42) } } },
		{ "vector3",{ _Param(vector3),{ _REQUIREDBY("test") } } },
		{ "isNotHere",{ _Param(isNotHere),{ _REQUIRED() } } },
		{ "intList",{ _List(intList),{ _MAX(2) } } },
		{ "floatList",{ _List(floatList),{ _EXCLUDEDBY("answer") } } },
		{ "boolList",{ _List(boolList),{} } },
		{ "stringList",{ _List(stringList, "#"),{ _EXCLUDEDBY("test") } } },
		{ "vector3List",{ _List(vector3List),{} } },
		{ "mixedList",{ mixedList.GetMapping(),{} } },
		{ "BLOCKLIST 1",{ _Block<MixedListDemo>(blockDemo),{} } },
		{ "Model 1",{ _Model<MyModel>(myModel),{} } }
	};
}

Oparse::OpMixedList * MixedListDemo::GetMapping()
{
	return _MixedList(OpValues() =
		{
			{ _Param(first),{ _ISANYOF(vector<string>() = { "a vector3" }) } },
		{ _Param(vector3),{} },
		{ _Param(second),{ _ISANYOF(vector<string>() = { "a vector3" }) } },
		{ _Param(testSuccessful),{} },
		{ _Param(third),{ _LENGTH(0, 256) } }
		}, ",");
}