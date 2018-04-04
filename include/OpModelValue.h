#pragma once


namespace Oparse
{
	class OpValidator;

	class OpModelValue
		: public OpValue
	{
	public:
		OpModelValue(OpModel *model) : modelDef(model->GetModelDef()) {};
		~OpModelValue() {};

		void ParseValue(string value);

		OpModelDef &GetModelDef();

	private:
		OpModelDef modelDef;
	};
}