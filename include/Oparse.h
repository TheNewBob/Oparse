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
#include "OpModel.h"
#include "OpMixedList.h"
#include "OpBlockList.h"
#include "OpLambda.h"

#include "OpvRequired.h"
#include "OpNumericValidator.h"
#include "OpvLength.h"
#include "OpvStringEquals.h"
#include "OpvConditionalRequired.h"




using namespace std;


namespace Oparse
{
	// Value factories
	OpInt *_Param(int &receiver);
	OpFloat *_Param(float &receiver);
	OpDouble *_Param(double &receiver);
	OpString *_Param(string &receiver, bool tolower = false);
	OpBool *_Param(bool &receiver);
	OpVector3 *_Param(VECTOR3 &receiver);
	OpLambda * _Param(function<string(string value)> lambda, bool tolower = false);
	OpReadWriteLambda * _Param(function<string(string value)> readLambda, function<string()> writeLambda, bool tolower = false);
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
	template <typename T> OpModel<T> *_ModelPtr(T *receiver) { return new OpModel<T>(receiver); };
	template <typename T, typename U = T> OpModelFactory<T, U> *_ModelFactory(vector<U*> &receiver) { return new OpModelFactory<T, U>(receiver); };

	//validator factories
	OpvRequired *_REQUIRED();
	OpvConditionalRequiredByParam * _REQUIREDBY(string paramName);
	OpvConditionalRequiredByParamValue *_REQUIREDBY(string paramName, int value);
	OpvConditionalRequiredByParamValue *_REQUIREDBY(string paramName, bool value);
	OpvConditionalRequiredByParamValue *_REQUIREDBY(string paramName, string value);
	OpvConditionalRequiredByParam *_EXCLUDEDBY(string paramName);
	OpNumericValidator *_MAX(double max);
	OpNumericValidator *_MIN(double min);
	OpNumericValidator *_RANGE(double min, double max);
	OpvLength *_LENGTH(unsigned int max);
	OpvLength *_LENGTH(unsigned int min, unsigned int max);
	OpvStringEquals *_ISANYOF(vector<string> allowedValues, bool caseSensitive = false);

	/**
	 * \brief Merges two model definitions together. If a key exists in both defOne and defTwo, the definition of defTwo will be applied.
	 * \note Keys are NOT treated as case-insensitive for merging!
	 */
	OpModelDef MergeModelDefs(const OpModelDef &defOne, const OpModelDef &def2);

	PARSINGRESULT ParseFile(string path, OpModelDef &mapping);
	void WriteFile(string path, OpModelDef &mapping);

	PARSINGRESULT ParseString(string data, OpModelDef &mapping, string name = "parsed from string");
	void WriteString(string &OUT_receiver, OpModelDef &mapping);

#ifndef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root = ROOT);
	PARSINGRESULT ParseFile(FILEHANDLE file, OpModelDef &mapping, string filename = "unspecified");
	void WriteToFile(FILEHANDLE file, OpModelDef &mapping);
#endif
	

}