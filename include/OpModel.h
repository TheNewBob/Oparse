#pragma once

namespace Oparse
{

	typedef map<string, pair<Oparse::OpValue*, vector<Oparse::OpValidator*>>> OpModelDef;
	typedef vector<Oparse::OpValue*> OpValues;

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
		OpModel(T &receiver) : mapping(receiver.GetModelDef()) {}
		~OpModel() { clearModelDef(mapping); };

		void ParseValue(OpFile *file, PARSINGRESULT &result)
		{
			ParseBlock(file, mapping, result);
			setParsed();
		}

		void Validate(PARSINGRESULT &result)
		{
			validateParsedMap(mapping, result);
		}

	private:
		OpModelDef mapping;
	};



	/**
	 * \brief Allocates a new model on the fly and adds it to the passed vector.
	 */
	template <class T, class U>
	class OpModelFactory
		: public OpModelFactoryFacade
	{
	public:

		/**
		 * \brief Creates a model factory where T is the type to be instatiated, and U is the type in which the models are stored.
		 * \note It is expected that T inherits U, and that T provides a method OpModelDef GetModelDef().
		 */
		OpModelFactory<T, U>(vector<U*> &receiver) : receiver(receiver) {};
		~OpModelFactory() { clearModelDef(mapping); };

		void ParseValue(OpFile *file, PARSINGRESULT &result)
		{
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

	private:
		vector<U*> &receiver;
		OpModelDef mapping;
	};

}