#pragma once

namespace Oparse
{

#ifdef OPARSE_STANDALONE
	struct VECTOR3
	{
		double x = 0;
		double y = 0;
		double z = 0;
	};
#endif

	class OpVector3 :
		public OpValue
	{
	public:
		OpVector3(VECTOR3 &receiver);
		~OpVector3() {};

		void ParseValue(string key, string value, PARSINGRESULT &result);

		void *GetValue() { return &receiver; };

	private:
		VECTOR3 &receiver;
	};

}