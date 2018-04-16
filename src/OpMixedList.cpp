#include "OpStdLibs.h"
#include "Oparse.h"

namespace Oparse
{


	OpMixedList::OpMixedList(OpValues receivers, string delimiter): OpValue(OP_MIXEDLIST), receivers(receivers), delimiter(delimiter)
	{
	}

	OpMixedList::~OpMixedList()
	{
		for (unsigned int i = 0; i < receivers.size(); ++i)
		{
			delete receivers[i].first;
			auto validators = receivers[i].second;
			for (unsigned int j = 0; j < validators.size(); ++j)
			{
				delete validators[j];
			}
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
				receivers[i].first->ParseValue(key, elements[i], result);
			}
			setParsed();
		}
	}


	void OpMixedList::Validate(string paramName, PARSINGRESULT & result)
	{
		for (unsigned int i = 0; i < receivers.size(); ++i)
		{
			auto validators = receivers[i].second;
			for (unsigned int j = 0; j < validators.size(); ++j)
			{
				validators[j]->Validate(receivers[i].first, paramName, result);
			}

		}
	}
}