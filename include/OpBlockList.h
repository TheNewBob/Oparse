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

		void Serialize(string key, stringstream & stream, unsigned int indents)
		{
			string tabs;
			for (unsigned int i = 0; i < indents; ++i)
			{
				tabs += "\t";
			}
			stream << tabs << "BEGIN_" << key << endl << valueAsString(indents + 1) << tabs << "END_" << key << endl;
		}

		string ValueAsString()
		{
			return valueAsString(0);
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

		string valueAsString(unsigned int indents)
		{
			string tabs;
			for (unsigned int i = 0; i < indents; ++i)
			{
				tabs += "\t";
			}

			stringstream ss;
			if (ptrs)
			{
				for (unsigned int i = 0; i < ptrReceiver.size(); ++i)
				{
					OpMixedList *mapping = ptrReceiver[i]->GetMapping();
					ss << tabs << mapping->ValueAsString() << endl;
					delete mapping;
				}
			}
			else
			{
				for (unsigned int i = 0; i < receiver.size(); ++i)
				{
					OpMixedList *mapping = receiver[i].GetMapping();
					ss << tabs << mapping->ValueAsString() << endl;
					delete mapping;
				}
			}
			return ss.str();

		}
	};
}