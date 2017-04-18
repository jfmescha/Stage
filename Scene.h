#pragma once
#include "Director.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Scene
{
private:
	//Scene ID
	int SceneID;
	//Scene File Name
	std::string SceneSet;
	//Scene Director list
	std::vector<Director> DirectorList;
	//Scene Director List Size
	int DirListSize;
	//Director Locator
	int DirectorLocator(int);

public:
	//Init
	//Constructor
	Scene();
	Scene(std::string);
	//Deconstructor
	~Scene();

	//Load scene
	void LoadScene();
	void AddDirector(std::string);

};
