#include "Scene.h"

int Scene::DirectorLocator(int id)
{
	for (int i = 0; i < DirectorList.size(); i++)
	{
		if (DirectorList[i].RequestID() == id)
			return i;
	}
	return 0;
}

Scene::Scene()
{
}

Scene::Scene(std::string filename)
{
	SceneSet = filename;
	DirListSize = 0;
}

Scene::~Scene()
{
	std::vector<Director>().swap(DirectorList);
}

void Scene::LoadScene()
{
	//File Reader
	std::ifstream SetReader;
	SetReader.open(SceneSet, std::ifstream::in);
	std::string parser = "NULL";

	int line = 0;
	int dirsize = 0;
	while (SetReader.eof() != true)
	{
		line++;
		std::getline(SetReader, parser);
		if (line > 2 && line <= dirsize + 2)
			AddDirector(parser);
		
		if (parser.find(':') != std::string::npos && line == 1)
		{
			std::size_t posS = parser.find("(");
			std::size_t posE = parser.find(")");
			std::string tempS = parser.substr(posS + 1, posE - posS - 1);
			SceneID = std::stoi(tempS);
		}
		if (parser.find(':') != std::string::npos && line == 2)
		{
			std::size_t posS = parser.find("(");
			std::size_t posE = parser.find(")");
			std::string tempS = parser.substr(posS + 1, posE - posS - 1);
			dirsize = std::stoi(tempS);
		}
	}
	SetReader.close();
}

void Scene::AddDirector(std::string dirFile)
{
	DirListSize++;
	DirectorList.resize(DirListSize);
	Director tempDir(dirFile);
	DirectorList[DirListSize - 1] = tempDir;
	std::cout << DirectorList[DirListSize - 1].RequestID() << std::endl;
}
