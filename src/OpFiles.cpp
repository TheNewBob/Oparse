#include "OpStdLibs.h"
#ifndef OPARSE_STANDALONE
#include "orbitersdk.h"
#endif
#include "OpFiles.h"

namespace Oparse
{

#ifdef OPARSE_STANDALONE

	OpStandaloneFile::OpStandaloneFile(string filename, bool write)
	{
		if (write)
		{
			file.open(filename, ios::out);

		}
		else {
			file.open(filename, ios::in);
		}
		if (!file.is_open()) throw runtime_error("Could not open file: " + filename);
	}

	OpStandaloneFile::~OpStandaloneFile()
	{
		file.close();
	}

	bool OpStandaloneFile::NextLine(string &OUT_line)
	{
		getline(file, OUT_line);
		return !file.eof();
	}

	void OpStandaloneFile::WriteStream(stringstream & stream)
	{
		file << stream.str();
	}

#else

	OpOrbiterFile::OpOrbiterFile(string filename, PathRoot root)
	{
		file = oapiOpenFile(filename.data(), FILE_IN_ZEROONFAIL, root);
		if (file == NULL) throw runtime_error("Could not open file: " + filename);
	}

	OpOrbiterFile::OpOrbiterFile(FILEHANDLE file): file(file)
	{
		resetFile();
	}

	bool OpOrbiterFile::NextLine(string &OUT_line)
	{
		char *l;
		bool result = oapiReadScenario_nextline(file, l);
		if (result) 
		{
			OUT_line = l;
		}
		return result;
	}

	void OpOrbiterFile::resetFile()
	{
		char l[500];
		oapiReadItem_string(file, (char*)"Module", l);
	}

#endif

}