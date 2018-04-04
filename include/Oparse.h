#pragma once

#include "StringOps.h"
#include "PARSINGRESULT.h"

#include "OpValue.h"
#include "OpValidator.h"

#include "OpInt.h"
#include "OpFloat.h"
#include "OpDouble.h"
#include "OpString.h"
#include "OpBool.h"
#include "OpVector3.h"
#include "OpList.h"
#include "OpMixedList.h"
#include "OpBlockList.h"
#include "OpModel.h"
#include "OpModelValue.h"

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
	OpVector3 *_Vector3(VECTOR3 &receiver);
	OpList *_LIST(vector<int> &receiver, string delimiter = ",\t");
	OpList *_LIST(vector<float> &receiver, string delimiter = ",\t");
	OpList *_LIST(vector<double> &receiver, string delimiter = ",\t");
	OpList *_LIST(vector<bool> &receiver, string delimiter = ",\t");
	OpList *_LIST(vector<string> &receiver, string delimiter = ",\t");
	OpList *_LIST(vector<VECTOR3> &receiver, string delimiter = ",\t");
	OpMixedList *_MixedList(OpValues receivers, string delimiter = "\t");
	template <typename T> OpBlockList<T> *_Block(vector<T> &receiver) { return new OpBlockList<T>(receiver); };
	template <typename T> OpBlockList<T> *_Block(vector<T*> &receiver) { return new OpBlockList<T>(receiver); };

	//validator factories
	OpvRequired *_REQUIRED();


	//const string WHITESPACE;

#ifdef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping);
#else
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root = ROOT);
	PARSINGRESULT ParseFile(FILEHANDLE file, OpModelDef &mapping);
#endif

}