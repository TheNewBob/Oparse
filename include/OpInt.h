#pragma once

namespace Oparse
{

	class OpInt :
		public OpValue
	{
	public:
		OpInt(int &receiver);
		~OpInt();

		void ParseValue(string key, string value, PARSINGRESULT &result);

		string ValueAsString();

		void *GetValue() { return &receiver; };

	private:
		int &receiver;
	};

}