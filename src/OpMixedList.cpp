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

	void Oparse::OpMixedList::ParseValue(string value)
	{
		vector<string> elements;
		SplitString(value, elements, delimiter);
		if (elements.size() != receivers.size())
			throw runtime_error("MixedList formatting error: number of elements in file does not match number of mapped elements!");

		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			receivers[i]->ParseValue(elements[i]);
		}
		setParsed();
	}
}