namespace Oparse
{
	class OpvStringEquals
		: public OpValidator
	{
	public:
		OpvStringEquals(vector<string> allowedValues, bool caseSensitive = false);

		void Validate(OpValue *value, const string paramName, PARSINGRESULT &result);

	private:
		vector<string> allowedValues;
		bool caseSensitive;
		bool isApplicableTo(OpValue *value);
	};

}