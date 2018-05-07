#pragma once


namespace Oparse
{

	class OpFile
	{
	public:

		virtual bool NextLine(string &OUT_line) = 0;
		virtual void WriteStream(stringstream &stream) = 0;
	};

#ifdef OPARSE_STANDALONE
	class OpStandaloneFile
		: public OpFile
	{
	public:
		OpStandaloneFile(string filename, bool write = false);
		~OpStandaloneFile();

		bool NextLine(string &OUT_line);

		void WriteStream(stringstream &stream);

	private:
		fstream file;
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
		void resetFile();
		FILEHANDLE file = NULL;
	};

#endif
}