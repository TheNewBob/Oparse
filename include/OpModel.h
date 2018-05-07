#pragma once

namespace Oparse
{

	typedef map<string, pair<Oparse::OpValue*, vector<Oparse::OpValidator*>>> OpModelDef;
	typedef vector<pair<Oparse::OpValue*, vector<Oparse::OpValidator*>>> OpValues;

	void ParseBlock(OpFile *file, OpModelDef &mapping, PARSINGRESULT &result);
	void clearModelDef(OpModelDef &mapping);
	void validateParsedMap(OpModelDef &mapping, PARSINGRESULT &result);

	/**
	 * \brief Base class for nestable values.
	 */
	class OpNestable
		: public OpValue
	{
	public:
		OpNestable(OP_TYPE type) : OpValue(type) {};
		virtual ~OpNestable() {};
		virtual void ParseValue(OpFile *file, PARSINGRESULT &result) = 0;
		virtual void Validate(PARSINGRESULT &result) = 0;
	private:
		void ParseValue(string key, string value, PARSINGRESULT &result) { throw runtime_error("ParseValue(string, string, PARSINGRESULT&) should never be called on a nestable class!"); };
	};


	/**
 	 * \brief Maps a model of type T that provides a method with signature OpModelDef GetModelDef().
	 */
	template <class T>
	class OpModel
		: public OpNestable
	{
	public:
		OpModel(T &receiver) : OpNestable(OP_MODEL), mapping(receiver.GetModelDef()) {}
		virtual ~OpModel() { clearModelDef(mapping); };

		void ParseValue(OpFile *file, PARSINGRESULT &result)
		{
			ParseBlock(file, mapping, result);
			setParsed();
		}

		void Validate(PARSINGRESULT &result)
		{
			validateParsedMap(mapping, result);
		}

		void Serialize(string key, stringstream &stream, unsigned int indents)
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

	private:
		OpModelDef mapping;

		string valueAsString(unsigned int indents)
		{
			stringstream ss;
			for (auto i = mapping.begin(); i != mapping.end(); ++i)
			{
				i->second.first->Serialize(i->first, ss, indents);
			}

			return ss.str();
		}

	};



	/**
	 * \brief Allocates a new model on the fly and adds a pointer to it to the passed vector.
	 */
	template <class T, class U>
	class OpModelPtrFactory
		: public OpNestable
	{
	public:

		/**
		 * \brief Creates a model factory where T is the type to be instatiated, and U is the type in which the models are stored.
		 * \note It is expected that T inherits U, and that T provides a method OpModelDef GetModelDef().
		 */
		OpModelPtrFactory<T, U>(vector<U*> &receiver) : OpNestable(OP_MODELFACTORY), receiver(receiver) {};
		virtual ~OpModelPtrFactory() { clearModelDef(mapping); };

		void ParseValue(OpFile *file, PARSINGRESULT &result)
		{
			//if (!WasParsed()) receiver.clear();
			T *newModel = new T;
			OpModelDef mapping = newModel->GetModelDef();
			receiver.push_back(newModel);
			ParseBlock(file, mapping, result);
			setParsed();
			clearModelDef(mapping);
		};

		void Validate(PARSINGRESULT &result)
		{
			for (unsigned int i = 0; i < receiver.size(); ++i)
			{
				OpModelDef mapping = receiver[i]->GetModelDef();
				validateParsedMap(mapping, result);
				clearModelDef(mapping);
			}
		};

		void Serialize(string key, stringstream &stream, unsigned int indents)
		{
			throw runtime_error("OpModelPtrFactory cannot be serialized!");
		};

		string ValueAsString() { return ""; };

		void *GetValue() { return &receiver; };

	private:
		vector<U*> &receiver;
	};

	/**
	* \brief Allocates a new model on the fly and it to the passed vector.
	*/
	template <class T>
	class OpModelFactory
		: public OpNestable
	{
	public:

		OpModelFactory<T>(vector<T> &receiver) : OpNestable(OP_MODELFACTORY), receiver(receiver) {};
		virtual ~OpModelFactory() {};

		void ParseValue(OpFile *file, PARSINGRESULT &result)
		{
			//if (!WasParsed()) receiver.clear();
			receiver.push_back(T());
			OpModelDef mapping = receiver.back().GetModelDef();
			ParseBlock(file, mapping, result);
			setParsed();
			clearModelDef(mapping);
		}

		void Validate(PARSINGRESULT &result)
		{
			for (unsigned int i = 0; i < receiver.size(); ++i)
			{
				OpModelDef mapping = receiver[i].GetModelDef();
				validateParsedMap(mapping, result);
				clearModelDef(mapping);
			}
		}

		void *GetValue() { return &receiver; };

		void Serialize(string key, stringstream &stream, unsigned int indents)
		{
			throw runtime_error("OpModelFactory cannot be serialized!");
		};

		string ValueAsString() { return ""; };

	private:
		vector<T> &receiver;
	};

}