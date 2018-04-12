#pragma once

namespace Oparse
{
	/**
	* \brief Is returned by parsing operations, containing errors and warnings encountered.
	*/
	struct PARSINGRESULT
	{
	public:
		string filename = "unspecified";
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

		/**
		 * \brief Returns a completely formatted error message for the given parameter, or an empty string if there are no errors for this parameter.
		 * \return A message formated like this: Parsing error in <filename> for parameter <paramname>: \n\t<error message>\n\t<error message>\n\t etc.
		 */
		string GetFormatedErrorsFor(string paramname)
		{
			string msgs = getErrorsFor(paramname, 1);
			if (msgs != "")
			{
				return "Parsing error in " + filename + " for parameter " + paramname + ":" + msgs;
			}
			return "";
		};

		/**
		 * \brief Returns a completely formatted error message for all errors in this file, or an empty string if there are no errors.
		 * \return A message formatted like this: Parsing errors in <filename>: \n\t for parameter <paramname>: \n\t\t <error message> ... \n\t for parameter <paramname>: etc./
		 */
		string GetFormattedErrorsForFile()
		{
			if (errors.size() > 0)
			{
				string errormsgs = "Parsing errors in " + filename;
				for (auto params = errors.begin(); params != errors.end(); ++params)
				{
					errormsgs += "\n\tfor parameter " + params->first + ":";
					errormsgs += getErrorsFor(params->first, 2);
				}
				return errormsgs;
			}
			return "";
		};

	private:
		map<string, vector<string>> errors;
		map<string, vector<string>> warnings;

		string getErrorsFor(string paramname, unsigned int numTabs)
		{
			auto errormsgs = errors.find(paramname);
			if (errormsgs != errors.end())
			{
				string errorstr = "";
				for (unsigned int i = 0; i < errormsgs->second.size(); ++i)
				{
					errorstr += "\n";
					for (unsigned int j = 0; j < numTabs; ++j)
					{
						errorstr += "\t";
					}
					errorstr += errormsgs->second[i];
				}
				return errorstr;
			}
			return "";
		};

	};
}
