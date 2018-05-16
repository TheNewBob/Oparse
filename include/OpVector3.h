#pragma once

#ifdef OPARSE_STANDALONE
struct VECTOR3
{
	double x = 0;
	double y = 0;
	double z = 0;
};
#endif


namespace Oparse
{
	class OpVector3 :
		public OpValue
	{
	public:
		OpVector3(VECTOR3 &receiver);
		~OpVector3() {};

		void ParseValue(string key, string value, PARSINGRESULT &result);

		string ValueAsString();

		void *GetValue() { return &receiver; };

	private:
		VECTOR3 &receiver;
	};

}