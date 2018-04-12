#pragma once

namespace Oparse
{
	class OpValue;
	class OpValidator;
	class OpMixedList;
	typedef map<string, pair<Oparse::OpValue*, vector<Oparse::OpValidator*>>> OpModelDef;
	typedef vector<Oparse::OpValue*> OpValues;
}
