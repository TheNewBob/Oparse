#pragma once

namespace Oparse
{
	class OpValue
	{
	public:
		OpValue() {};
		virtual ~OpValue() {};

		/**
		 * \brief Attempts to parse the string into an appropriate value and set it in the model.
		 * \throws if no sense could be made of the value (usually because it's of the wrong type).
		 */
		virtual void ParseValue(string value) = 0;
		
		/**
		 * \return True if this value was parsed, false if not.
		 */
		bool WasParsed() { return wasParsed; };

	protected:
		/**
		 * \brief Signify that this value has been succesfully parsed
		 */
		void setParsed() { wasParsed = true; }

	private:
		bool wasParsed = false;
	};
}
