#pragma once

namespace Oparse
{
	class OpString :
		public OpValue
	{
	public:
		OpString(string &receiver, bool toLower = false);
		~OpString();

		void ParseValue(string value);

	private:
		string & receiver;
		bool toLower;
	};
}
