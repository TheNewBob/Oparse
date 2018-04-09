#pragma once

namespace Oparse
{
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
		map<string, vector<string>> GetErrors() { return errors; };

		/**
		* \brief Add an error message to the result.
		*/
		void AddError(string param, string msg) { errors[param].push_back(msg); };

		/**
		* \brief Add a warning message to the result.
		*/
		void AddWarning(string param, string msg) { warnings[param].push_back(msg); };

		/**
		* \return All warning messages noted during a parsing operation.
		*/
		map<string, vector<string>> GetWarnings() { return warnings; };
	private:
		map<string, vector<string>> errors;
		map<string, vector<string>> warnings;

	};
}
