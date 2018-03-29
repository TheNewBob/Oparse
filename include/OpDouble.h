#pragma once

namespace Oparse
{

	class OpDouble :
		public OpValue
	{
	public:
		OpDouble(double &receiver);
		~OpDouble();

		void ParseValue(string value);

	private:
		double &receiver;
	};

}