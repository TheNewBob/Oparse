#pragma once

namespace Oparse
{
	class OpList 
		: public OpValue
	{
	public:
		// Not doing this with generics because it becomes a mess with header / source separation, 
		// and produces difficult to understand errors when somebody uses a type that is not supported.
		OpList(vector<int> &receiver, string delimiter = ",");
		OpList(vector<float> &receiver, string delimiter = ",");
		OpList(vector<double> &receiver, string delimiter = ",");
		OpList(vector<bool> &receiver, string delimiter = ",");
		OpList(vector<string> &receiver, string delimiter = ",");
		~OpList() {};

		void ParseValue(string value);

	private:
		void *receiver;
		int type = -1;
		string delimiter = ",";
	};
}
