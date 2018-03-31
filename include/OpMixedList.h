#pragma once

namespace Oparse
{
	/**
	 * \brief A list of determinate length where every element maps to an individual field.
	 */
	class OpMixedList
		:public OpValue
	{
	public:
		OpMixedList(vector<OpValue*> receivers, string delimiter = "\t");
		~OpMixedList();

		virtual void ParseValue(string value);

	private:
		vector<OpValue*> receivers;
		string delimiter;
	};
}