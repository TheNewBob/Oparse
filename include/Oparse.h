#pragma once

#include "StringOps.h"
#include "OpFiles.h"
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
	OpList *_List(vector<int> &receiver, string delimiter = ",\t");
	OpList *_List(vector<float> &receiver, string delimiter = ",\t");
	OpList *_List(vector<double> &receiver, string delimiter = ",\t");
	OpList *_List(vector<bool> &receiver, string delimiter = ",\t");
	OpList *_List(vector<string> &receiver, string delimiter = ",\t");
	OpList *_List(vector<VECTOR3> &receiver, string delimiter = ",\t");
	OpMixedList *_MixedList(OpValues receivers, string delimiter = "\t");
	template <typename T> OpBlockList<T> *_Block(vector<T> &receiver) { return new OpBlockList<T>(receiver); };
	template <typename T> OpBlockList<T> *_Block(vector<T*> &receiver) { return new OpBlockList<T>(receiver); };
	template <typename T> OpModel<T> *_Model(T &receiver) { return new OpModel<T>(receiver); };
	template <typename T, typename U = T> OpModelFactory<T, U> *_ModelFactory(vector<U*> &receiver) { return new OpModelFactory<T, U>(receiver); };
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