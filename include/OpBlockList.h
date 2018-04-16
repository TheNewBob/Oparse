#pragma once

namespace Oparse
{

	class OpBlockListFacade
		: public OpValue
	{
	public:
		OpBlockListFacade() : OpValue(OP_BLOCKLIST) {};
		virtual void Validate(string paramName, PARSINGRESULT &result) = 0;
	};


	template <class T>
	class OpBlockList
		: public OpBlockListFacade
	{
	public:
		OpBlockList<T>(vector<T> &receiver) : receiver(receiver), ptrReceiver(vector<T*>()) {};
		OpBlockList<T>(vector<T*> &receiver) : receiver(vector<T>()), ptrReceiver(receiver), ptrs(true) {};
		~OpBlockList() 
		{
			for (unsigned int i = 0; i < mappings.size(); ++i)
			{
				delete mappings[i];
			}
			mappings.clear();
		};

		void ParseValue(string key, string value, PARSINGRESULT &result)
		{
			if (ptrs)
			{
				//allocate new objects as pointers
				T *newItem = new T;
				OpMixedList *mapping = newItem->GetMapping();
				mapping->ParseValue(key, value, result);
				ptrReceiver.push_back(newItem);
				mappings.push_back(mapping);
			}
			else
			{
				T newItem;
				OpMixedList *mapping = newItem.GetMapping();
				mapping->ParseValue(key, value, result);
				receiver.push_back(newItem);
				mappings.push_back(mapping);
			}
			setParsed();
		}

		void *GetValue() { return NULL; };

		void Validate(string paramName, PARSINGRESULT &result)
		{
			for (unsigned int i = 0; i < mappings.size(); ++i)
			{
				mappings[i]->Validate(paramName, result);
			}
		}

	private:
		vector<T> &receiver;
		vector<T*> &ptrReceiver;
		bool ptrs = false;
		vector<OpMixedList*> mappings;
	};
}