#pragma once

namespace Oparse
{

	class OpFloat :
		public OpValue
	{
	public:
		OpFloat(float &receiver);
		~OpFloat();

		void ParseValue(string value);

	private:
		float &receiver;
	};

}