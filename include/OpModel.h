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

		void *GetValue() { return NULL; };

	private:
		OpModelDef mapping;
	};



	/**
	 * \brief Allocates a new model on the fly and adds it to the passed vector.
	 */
	template <class T, class U>
	class OpModelFactory
		: public OpNestable
	{
	public:

		/**
		 * \brief Creates a model factory where T is the type to be instatiated, and U is the type in which the models are stored.
		 * \note It is expected that T inherits U, and that T provides a method OpModelDef GetModelDef().
		 */
		OpModelFactory<T, U>(vector<U*> &receiver) : OpNestable(OP_MODELFACTORY), receiver(receiver) {};
		virtual ~OpModelFactory() { clearModelDef(mapping); };

		void ParseValue(OpFile *file, PARSINGRESULT &result)
		{
			if (!WasParsed()) receiver.clear();
			T newModel = new T;
			mapping = newModel->GetModelDef();
			ptrReceiver.push_back(newModel);
			ParseBlock(file, mapping, result);
			setParsed();
		}

		void Validate(PARSINGRESULT &result)
		{
			validateParsedMap(mapping, result);
		}

		void *GetValue() { return &receiver; };

	private:
		vector<U*> &receiver;
		OpModelDef mapping;
	};

}