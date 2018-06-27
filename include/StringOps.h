#pragma once

namespace Oparse
{
	/**
	* \return A string converted to lower case.
	*/
	string StringToLower(const string str);

	/**
	* \return A string with leading and trailing whitespace removed.
	*/
	string RemoveExtraWhiteSpace(string str);

	void SplitString(const string &str, vector<string> &OUT_result, const string &delimiters);

	bool StringContains(const string &str, const string lookFor);

	bool StringBeginsWith(const string &str, const string beginsWith);

	/**
	* \brief Replaces all occurances of lookFor in str with replaceWith.
	*/
	string StringReplace(const string &str, const std::string& lookFor, const std::string& replaceWith);
}