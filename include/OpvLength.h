namespace Oparse
{
	class OpvLength
		: public OpValidator
	{
	public:
		OpvLength(double min, double max) : min(min), max(max) {};

		void Validate(OpValue *value, const string paramName, PARSINGRESULT &result);
	
	private:
		double max;
		double min;

		bool isApplicableTo(OpValue *value);
	};
}