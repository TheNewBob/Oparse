#pragma once

namespace Oparse
{
	class OpString :
		public OpValue
	{
	public:
		OpString(string &receiver, bool toLower = false);
		~OpString();

		void ParseValue(string key, string value, PARSINGRESULT &result);

	private:
		string & receiver;
		bool toLower;
	};
}
