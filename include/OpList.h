#pragma once

namespace Oparse
{
	/**
	 * \brief A List of indeterminate length where every element has the same type.
	 */
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
		OpList(vector<VECTOR3> &receiver, string delimiter = ",");
		~OpList() {};

		void ParseValue(string key, string value, PARSINGRESULT &result);

		void *GetValue() { return receiver; };

		/**
		 * \return The type of the list elements.
		 */
		OP_TYPE GetListType() { return listType; };

		unsigned int GetSize() { return size; };

	private:

		void *receiver;
		OP_TYPE listType;
		string delimiter = ",";
		unsigned int size = 0;
	};
}
