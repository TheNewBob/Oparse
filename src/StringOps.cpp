#include "OpStdLibs.h"
#include <algorithm>
#include "..\include\StringOps.h"

namespace Oparse
{
	const string WHITESPACE = " \t";

	string StringToLower(string in)
	{
		string out = in;
		transform(out.begin(), out.end(), out.begin(), tolower);
		return out;
	}

	string RemoveExtraWhiteSpace(string str)
	{
		size_t newbegin = str.find_first_not_of(WHITESPACE);
		if (newbegin == string::npos)
		{
			//the passed string consists ONLY of whitespace
			return "";
		}
		size_t range = str.find_last_not_of(WHITESPACE) - newbegin + 1;
		str = str.substr(newbegin, range);
		return str;
	}

	void SplitString(const string &str, vector<string> &OUT_result, const string &delimiters)
	{
		// Skip delimiters at beginning.
		string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// Find first "non-delimiter".
		string::size_type pos = str.find_first_of(delimiters, lastPos);

		while (pos != string::npos || lastPos != string::npos) {
			// Found a token, add it to the vector.
			OUT_result.push_back(str.substr(lastPos, pos - lastPos));
			// Skip delimiters.  Note the "not_of"
			lastPos = str.find_first_not_of(delimiters, pos);
			// Find next "non-delimiter"
			pos = str.find_first_of(delimiters, lastPos);
		}
	}
	bool StringContains(const string & str, const string lookFor)
	{
		return (str.find(lookFor) != string::npos);
	}

	bool StringBeginsWith(const string & str, const string beginsWith)
	{
		return (str.compare(0, beginsWith.length(), beginsWith) == 0);
	}

	string StringReplace(const string &str, const std::string& lookFor, const std::string& replaceWith) 
	{
		string result = str;
		bool run = true;
		while (run) {
			size_t start_pos = result.find(lookFor);
			if (start_pos != std::string::npos)
			{
				result.replace(start_pos, lookFor.length(), replaceWith);
			}
			else
			{
				run = false;
			}
		}
		return result;
	}
}