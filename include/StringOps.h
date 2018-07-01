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

	/**
	 * \brief Splits str at any of the delimiters and populates OUT_result with the elements.
	 */
	void SplitString(const string &str, vector<string> &OUT_result, const string &delimiters);

	/**
	 * \return True if str contains lookFor, false otherwise.
	 */
	bool StringContains(const string &str, const string lookFor);

	/**
	 * \return True if string begins with beginsWith, false otherwise.
	 */
	bool StringBeginsWith(const string &str, const string beginsWith);

	/**
	 * \brief Replaces all occurances of lookFor in str with replaceWith.
	 */
	string StringReplace(const string &str, const std::string& lookFor, const std::string& replaceWith);
}