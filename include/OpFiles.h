#pragma once


namespace Oparse
{

	class OpFile
	{
	public:

		virtual bool NextLine(string &OUT_line) = 0;
	};

#ifdef OPARSE_STANDALONE
	class OpStandaloneFile
		: public OpFile
	{
	public:
		OpStandaloneFile(string filename);
		~OpStandaloneFile();

		bool NextLine(string &OUT_line);

	private:
		ifstream file;
	};
#else
	class OpOrbiterFile
		: public OpFile
	{
	public:
		OpOrbiterFile(string filename, PathRoot root);
		OpOrbiterFile(FILEHANDLE file);
		~OpOrbiterFile() {};
		bool NextLine(string &OUT_line);

	private:
		resetFile();
		FILEHANDLE file = NULL;
	};

#endif
}