namespace Oparse
{
	class OpvLength
		: public OpValidator
	{
	public:
		OpvLength(double minimum, double maximum) : minimum(minimum), maximum(maximum) {};

		void Validate(OpValue *value, const string paramName, PARSINGRESULT &result);
	
	private:
		double maximum;
		double minimum;

		bool isApplicableTo(OpValue *value);
	};
}