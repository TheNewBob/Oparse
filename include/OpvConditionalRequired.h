# pragma once

namespace Oparse
{

	class OpvConditionalRequiredFacade
		: public OpValidator
	{
	public:
		virtual void Validate(OpValue *value, string paramName, OpModelDef &mapping, PARSINGRESULT &result) = 0;

		virtual void Validate(OpValue *value, const string paramName, PARSINGRESULT &result)
		{
			result.AddWarning(paramName, "Invalid validation call on ConditionalRequired validator. Possibly the validator is used inside MixedList scope?");
		};


	protected:
		virtual bool isApplicableTo(OpValue *value) { return true; };
	};

	/**
	 * \brief Defines the optionality of a parameter based on the presence of another parameter.
	 * For example, you might have an optional parameter "crewmember" that defines the presence of a crewmember
	 * by containing his name. There may be no crewmembers, so this parameter is not required. However, if the crewmember
	 * is defined, you also need his age. Ergo, the parameter "crewmemberAge" is only required IF crewmember is present in the config.
	 * The same works for exclusions: You might want to define a "controllStation" parameter, but it is ONLY required if NO crewmember is defined,
	 * and it would be an error IF a crewmember was defined.
	 * \note This does not apply recursively. Any conditions apply only in the current model.
	 */
	class OpvConditionalRequiredByParam
		: public OpvConditionalRequiredFacade
	{
	public:
		/**
		 * \param exclusive Pass false if the presence of the other parameter indicates that this parameter is required, true if the two are mutually exclusive.
		 * \param paramName The name of the parameter that requires/excludes this parameter.
		 */
		OpvConditionalRequiredByParam(bool exclusive, string paramName) : exclusive(exclusive), otherParamName(StringToLower(paramName)) {};

		void Validate(OpValue *value, string paramName, OpModelDef &mapping, PARSINGRESULT &result);

	private:
		bool exclusive;
		string otherParamName;
	};

	/**
	 * \brief Makes a parameter required if another parameter has a specific value, or forbidden if the other parameter does not match that value.
	 * \note the parameter requiring this one must be of either type string, int or bool (i.e. unambiguously comparable).
	 */
	class OpvConditionalRequiredByParamValue
		: public OpvConditionalRequiredFacade
	{
	public:
		OpvConditionalRequiredByParamValue(string paramName, string paramValue) : otherParamName(paramName), otherParamValue(new string(StringToLower(paramValue))), type(OP_STRING) {};
		OpvConditionalRequiredByParamValue(string paramName, int paramValue) : otherParamName(paramName), otherParamValue(new int(paramValue)), type(OP_INT) {};
		OpvConditionalRequiredByParamValue(string paramName, bool paramValue) : otherParamName(paramName), otherParamValue(new bool(paramValue)), type(OP_BOOL) {};

		void Validate(OpValue *value, string paramName, OpModelDef &mapping, PARSINGRESULT &result);

	private:
		string otherParamValueAsString();

		void *otherParamValue;
		string otherParamName;
		OP_TYPE type;
	};

}