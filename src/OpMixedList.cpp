#include "OpStdLibs.h"
#include "Oparse.h"

namespace Oparse
{

	Oparse::OpMixedList::OpMixedList(vector<OpValue*> receivers, string delimiter): receivers(receivers), delimiter(delimiter)
	{
	}

	Oparse::OpMixedList::~OpMixedList()
	{
		for (unsigned int i = 0; i < receivers.size(); ++i)
		{
			delete receivers[i];
		}
		receivers.clear();
	}

	void Oparse::OpMixedList::ParseValue(string key, string value, PARSINGRESULT &result)
	{
		vector<string> elements;
		SplitString(value, elements, delimiter);
		if (elements.size() != receivers.size())
		{
			result.AddError(key, "MixedList formatting error: number of elements in file does not match number of mapped elements!");
		}
		else
		{
			for (unsigned int i = 0; i < elements.size(); ++i)
			{
				receivers[i]->ParseValue(key, elements[i], result);
			}
			setParsed();
		}
	}
}