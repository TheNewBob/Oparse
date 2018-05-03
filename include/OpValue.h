#pragma once

namespace Oparse
{

	enum OP_TYPE
	{
		OP_INT,
		OP_FLOAT,
		OP_DOUBLE,
		OP_BOOL,
		OP_STRING,
		OP_VECTOR3,
		OP_LIST,
		OP_MIXEDLIST,
		OP_BLOCKLIST,
		OP_MODEL,
		OP_MODELFACTORY,
		OP_LAMBDA
	};

	class OpValue
	{
	public:
		OpValue(OP_TYPE type): type(type) {};
		virtual ~OpValue() {};

		/**
		 * \brief Attempts to parse the string into an appropriate value and set it in the model.
		 * \throws if no sense could be made of the value (usually because it's of the wrong type).
		 */
		virtual void ParseValue(string key, string value, PARSINGRESULT &result) = 0;
		
		/**
		 * \return True if this value was parsed, false if not.
		 */
		bool WasParsed() { return wasParsed; };

		/**
		 * \returns the type of this value
		 */
		OP_TYPE GetType() { return type; };

		/**
		 * \return A pointer to the actual value this parser is maped to.
		 */
		virtual void *GetValue() = 0;

		static string GetTypeDescriptionFor(OP_TYPE type)
		{
			switch (type)
			{
			case OP_INT: return "int";
			case OP_BOOL: return "bool";
			case OP_FLOAT: return "float";
			case OP_DOUBLE: return "double";
			case OP_STRING: return "string";
			case OP_LIST: return "List";
			case OP_MIXEDLIST: return "MixedList";
			case OP_BLOCKLIST: return "BlockList";
			case OP_MODEL: return "Model";
			case OP_MODELFACTORY: return "ModelFactory";
			default: return "Unknown Type";
			}
		}
	protected:
		/**
		 * \brief Signify that this value has been succesfully parsed
		 */
		void setParsed() { wasParsed = true; }

	private:
		bool wasParsed = false;
		OP_TYPE type;
	};
}
