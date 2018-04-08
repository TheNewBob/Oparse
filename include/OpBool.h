#pragma once

namespace Oparse
{
	class OpBool : 
		public OpValue
	{
	public:
		OpBool(bool &receiver);
		~OpBool();

		void ParseValue(string key, string value, PARSINGRESULT &result);

	private:
		bool &receiver;
	};
}