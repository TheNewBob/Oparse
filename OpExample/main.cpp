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

	OpModelDef mapping = {
		{ "answer", _Int(answer) },
		{ "sqrt2", _Float(sqrt2) },
		{ "pi", _Double(pi) },
		{ "question", _String(question) },
		{ "makesSense", _Bool(makesSense)}
	};

	auto result = ParseFile(
		"testme.cfg",
		mapping
	);

	bool bugme = true;

}