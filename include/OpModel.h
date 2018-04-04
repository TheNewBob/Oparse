#pragma once

typedef map<string, pair<Oparse::OpValue*, vector<Oparse::OpValidator*>>> OpModelDef;
typedef vector<Oparse::OpValue*> OpValues;

namespace Oparse
{
	/**
	* \brief Interface for models.
	* Inherit this class and return your mapping in an override of GetModelDef().
	*/
	class OpModel
	{
	public:
		virtual OpModelDef GetModelDef() = 0;
	};
}