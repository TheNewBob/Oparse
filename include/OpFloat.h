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

		string ValueAsString();

		void *GetValue() { return &receiver; };

	private:
		float &receiver;
	};

}