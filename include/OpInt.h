#pragma once

namespace Oparse
{

	class OpInt :
		public OpValue
	{
	public:
		OpInt(int &receiver);
		~OpInt();

		void ParseValue(string value);

	private:
		int &receiver;
	};

}