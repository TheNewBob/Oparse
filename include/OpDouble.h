#pragma once

namespace Oparse
{

	class OpDouble :
		public OpValue
	{
	public:
		OpDouble(double &receiver);
		~OpDouble();

		void ParseValue(string key, string value, PARSINGRESULT &result);

		void *GetValue() { return &receiver; };

	private:
		double &receiver;
	};

}