#pragma once

typedef map<string, pair<Oparse::OpValue*, vector<Oparse::OpValidator*>>> OpModelDef;
typedef vector<Oparse::OpValue*> OpValues;

namespace Oparse
{
	/**
	* \brief Base class for models.
	* Inherit this class and pass your mapping to the constructor.
	*/
	class OpModel
		: public OpValue
	{
	public:
		OpModel(OpModelDef mapping) : mapping(mapping) {};
		OpModelDef &GetModelDef() { return mapping; };

	private:
		void ParseValue(string key, string value, PARSINGRESULT &result) { throw runtime_error("OpModel::ParseValue() should never be called!"); };
		OpModelDef mapping;
	};
}