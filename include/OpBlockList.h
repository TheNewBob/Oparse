#pragma once

namespace Oparse
{
	template <class T>
	class OpBlockList
		: public OpValue
	{
	public:
		OpBlockList<T>(vector<T> &receiver) : receiver(receiver), ptrReceiver(vector<T*>()) {};
		OpBlockList<T>(vector<T*> &receiver) : receiver(vector<T>()), ptrReceiver(receiver), ptrs(true) {};
		~OpBlockList() {};

		void ParseValue(string value)
		{
			if (ptrs)
			{
				//allocate new objects as pointers
				T *newItem = new T;
				OpMixedList *mapping = newItem->GetMapping();
				mapping->ParseValue(value);
				ptrReceiver.push_back(newItem);
			}
			else
			{
				T newItem;
				OpMixedList *mapping = newItem.GetMapping();
				mapping->ParseValue(value);
				receiver.push_back(newItem);
			}
			setParsed();
		}

	private:
		vector<T> &receiver;
		vector<T*> &ptrReceiver;
		bool ptrs = false;
	};
}