#pragma once

namespace Oparse
{

	class OpModelFactoryFacade
		: public OpValue
	{
	public:
		virtual OpModel *CreateNewModel() = 0;
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
		 * \note It is expected that U inherits OpModel, and T inherits U.
		 */
		OpModelFactory<T, U>(vector<U*> &receiver) : receiver(receiver) {};

		OpModel *CreateNewModel()
		{
			T newModel = new T;
			ptrReceiver.push_back(newModel);
			return newModel;
		}

	private:
		void ParseValue(string key, string value, PARSINGRESULT &result) { throw runtime_error("OpModelFactory::ParseValue() should never be called!"); };
		vector<U*> &receiver;
	};
}