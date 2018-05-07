//#define OPARSE_STANDALONE
#include "OpStdLibs.h"
#include "Oparse.h"
#include "NestedModel.h"
#include "MyModel.h"
#include "DemoModel.h"

using namespace Oparse;


int main()
{
	DemoModel demo;
	
	auto result = Oparse::ParseFile(
		"testme.cfg",
		demo.GetModelDef()
	);

	Oparse::WriteFile(
		"testout.cfg", 
		demo.GetModelDef());

	bool bugme = true;

}