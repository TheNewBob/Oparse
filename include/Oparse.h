#pragma once
#include "StringOps.h"
#include "PARSINGRESULT.h"

#include "OpValue.h"
#include "OpInt.h"
#include "OpFloat.h"
#include "OpDouble.h"
#include "OpString.h"
#include "OpBool.h"

#include "OpValidator.h"
#include "OpvRequired.h"



using namespace std;


namespace Oparse
{
	// Value factories
	OpInt *_Int(int &receiver);
	OpFloat *_Float(float &receiver);
	OpDouble *_Double(double &receiver);
	OpString *_String(string &receiver);
	OpBool *_Bool(bool &receiver);

	
	
	extern OpvRequired REQUIRED;

	typedef map<string, pair<OpValue*, vector<OpValidator*>>> OpModelDef;

	//const string WHITESPACE;

#ifdef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping);
#else
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root = ROOT);
	PARSINGRESULT ParseFile(FILEHANDLE file, OpModelDef &mapping);
#endif

}