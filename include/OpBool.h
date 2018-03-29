#pragma once

namespace Oparse
{
	class OpBool : 
		public OpValue
	{
	public:
		OpBool(bool &receiver);
		~OpBool();

		void ParseValue(string value);

	private:
		bool &receiver;
	};
}