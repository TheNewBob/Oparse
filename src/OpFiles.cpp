#include "OpStdLibs.h"
#ifndef OPARSE_STANDALONE
#include "orbitersdk.h"
#endif
#include "OpFiles.h"

namespace Oparse
{

#ifdef OPARSE_STANDALONE

	OpStandaloneFile::OpStandaloneFile(string filename)
	{
		file.open(filename);
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

#else

	OpOrbiterFile::OpOrbiterFile(string filename, PathRoot root)
	{
		file = oapiOpenFile(path.data(), FILE_IN_ZEROONFAIL, root);
		if (file == NULL) throw runtime_error("Could not open file: " + filename);
	}

	OpOrbiterFile::OpOrbiterFile(FILEHANDLE file) file(file)
	{
		resetFile(file);
	}

	bool OpOrbiterFile::NextLine(string &OUT_line)
	{
		char *l;
		auto result = oapiReadScenario_nextline(file, l);
		OUT_line = l;
		return result;
	}

	OpOrbiterFile::resetFile()
	{
		char l[500];
		oapiReadItem_string(file, (char*)"Module", l);
	}

#endif

}