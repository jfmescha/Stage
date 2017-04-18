#include "FileIO.h"

FileIO::FileIO(std::string filename, std::string fileexe)
{
	FileName = filename;
	FileType = fileexe;
}

void FileIO::OpenFile()
{
	if (FileWrite.is_open())
	{

	}
}

void FileIO::ActorSheetLoad()
{

	FileRead.open(FileName + FileType, std::ifstream::in);
	std::string parser = "NULL";

	while (FileRead.eof() != true)
	{
		std::getline(FileRead, parser);

		std::cout << parser << std::endl;

		if (parser.find(':') != std::string::npos)
		{
			std::size_t posS = parser.find("(");
			std::size_t posE = parser.find(")");
			std::string tempS = parser.substr(posS+1, posE-posS-1);
			std::cout << tempS << std::endl;
		}
	}

}
