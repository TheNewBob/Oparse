#pragma once
#include "OpValue.h"
#include "OpInt.h"
#include "OpFloat.h"
#include "OpDouble.h"
#include "OpString.h"
#include "StringOps.h"
#include "OpBool.h"

using namespace std;

namespace Oparse
{
	typedef map<string, OpValue*> OpModelDef;

	// QuickFactories for OpValue classes
	OpInt *_Int(int &receiver);
	OpFloat *_Float(float &receiver);
	OpDouble *_Double(double &receiver);
	OpString *_String(string &receiver);
	OpBool *_Bool(bool &receiver);

	/**
	* \brief Is returned by parsing operations, containing errors and warnings encountered.
	*/
	struct PARSINGRESULT
	{
	public:
		/**
		* \return true if there were errors during a parsing operation, false otherwise.
		*/
		bool HasErrors() { return errors.size() > 0; };

		/**
		* \return True if there were warnings during a parsing operation, false otherwise.
		*/
		bool HasWarnings() { return warnings.size() > 0; };

		/**
		* \return All error messages noted during a parsing operation.
		*/
		vector<string> GetErrors() { return errors; };

		/**
		* \brief Add an error message to the result.
		*/
		void AddError(string msg) { errors.push_back(msg); };

		/**
		* \brief Add a warning message to the result.
		*/
		void AddWarning(string msg) { warnings.push_back(msg); };

		/**
		* \return All warning messages noted during a parsing operation.
		*/
		vector<string> GetWarnings() { return warnings; };
	private:
		vector<string> errors;
		vector<string> warnings;

	};

	//const string WHITESPACE;

#ifdef OPARSE_STANDALONE
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping);
#else
	PARSINGRESULT ParseFile(string path, OpModelDef &mapping, PathRoot root = ROOT);
	PARSINGRESULT ParseFile(FILEHANDLE file, OpModelDef &mapping);
#endif

}