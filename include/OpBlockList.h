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
		};

		void ParseValue(string key, string value, PARSINGRESULT &result)
		{
			if (ptrs)
			{
				if (!WasParsed()) ptrReceiver.clear();
				//allocate new objects as pointers
				T *newItem = new T;
				OpMixedList *mapping = newItem->GetMapping();
				mapping->ParseValue(key, value, result);
				ptrReceiver.push_back(newItem);
				delete mapping;
			}
			else
			{
				if (!WasParsed()) receiver.clear();
				T newItem;
				OpMixedList *mapping = newItem.GetMapping();
				mapping->ParseValue(key, value, result);
				receiver.push_back(newItem);
				delete mapping;
			}
			setParsed();
		}

		void *GetValue() { return NULL; };

		void Validate(string paramName, PARSINGRESULT &result)
		{
			for (unsigned int i = 0; i < receiver.size(); ++i)
			{
				OpMixedList *mapping;
				if (ptrs)
				{
					mapping = ptrReceiver[i]->GetMapping();
				}
				else
				{
					mapping = receiver[i].GetMapping();
				}
				mapping->Validate(paramName, result);
				delete mapping;
			}
		}

	private:
		vector<T> &receiver;
		vector<T*> &ptrReceiver;
		bool ptrs = false;
	};
}