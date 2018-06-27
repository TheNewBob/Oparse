//#define OPARSE_STANDALONE
#include "OpStdLibs.h"
#include "Oparse.h"
#include "NestedModel.h"
#include "MyModel.h"
#include "DemoModel.h"

using namespace Oparse;


int main()
{
	// instantiate two models for demonstration
	DemoModel fileDemo;
	DemoModel stringDemo;
	
	// map the file testme.cfg to the fileDemo object.
	auto result = Oparse::ParseFile(
		"testme.cfg",
		fileDemo.GetModelDef()
	);

	// Serialise fileDemo into a string.
	string fileContents;
	Oparse::WriteString(fileContents, fileDemo.GetModelDef());

	// map the resulting string to the stringDemo object. 
	// fileDemo and stringDemo will have identical contents, which is a bit pointless from a practical standpoint, but a nice demo.
	Oparse::ParseString(fileContents, stringDemo.GetModelDef(), "string deserialisation demo");

	// Finally, serialise the stringDemo object to a file on disk:
	Oparse::WriteFile(
		"testout.cfg", 
		stringDemo.GetModelDef());

	// set breakpoint here to take a look at the mapped objects.
	bool bugme = true;

}