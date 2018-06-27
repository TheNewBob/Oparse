#include "OpStdLibs.h"
#ifndef OPARSE_STANDALONE
#include "orbitersdk.h"
#endif
#include "OpFiles.h"

namespace Oparse
{



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

#ifndef OPARSE_STANDALONE
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

	void OpOrbiterFile::WriteStream(stringstream & stream)
	{
		char line[2048];
		while (!stream.eof())
		{
			stream.getline(line, 2048);
			oapiWriteLine(file, line);
		}


	}

	void OpOrbiterFile::resetFile()
	{
		char l[500];
		oapiReadItem_string(file, (char*)"Module", l);
	}
#endif

	OpMemoryFile::OpMemoryFile(string contents) : contents(contents) {}

	bool OpMemoryFile::NextLine(string & OUT_line)
	{
		getline(contents, OUT_line);
		return !contents.eof();
	}
	void OpMemoryFile::WriteStream(stringstream & stream)
	{
		contents << stream.str();
	}

	string OpMemoryFile::ToString()
	{
		return contents.str();
	}
}
