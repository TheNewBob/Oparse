#pragma once

namespace Oparse
{

	class OpFloat :
		public OpValue
	{
	public:
		OpFloat(float &receiver);
		~OpFloat();

		void ParseValue(string key, string value, PARSINGRESULT &result);

	private:
		float &receiver;
	};

}