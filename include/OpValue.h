#pragma once

namespace Oparse
{
	class OpValue
	{
	public:
		OpValue() {};
		virtual ~OpValue() {};

		virtual void ParseValue(string value) = 0;
	};
}
