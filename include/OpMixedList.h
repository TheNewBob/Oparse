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
		OpMixedList(OpValues receivers, string delimiter = "\t");
		~OpMixedList();

		virtual void ParseValue(string key, string value, PARSINGRESULT &result);

		void *GetValue() { return &receivers; };

		void Validate(string paramName, PARSINGRESULT &result);

	private:
		OpValues receivers;
		string delimiter;
	};
}