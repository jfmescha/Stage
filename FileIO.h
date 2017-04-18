#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class FileIO
{
private:
	std::string FileName;
	/* 
		.dss - DaiScript sheet.
		.sas - Stage actor sheet.
		.sdd - Stage director directory.
		.scn - Stage scene information.Holds info like maps, props, directors for the scene.
		.ssm - Stage scene map.
		.ssp - Stage scene prop.
		.bss - Basic system settings.Items like graphics settings, player bindings, ext.
		.scs - Stage Choreographed sheets
		.spn - Stage Particle node.
	*/
	std::string FileType;

	std::ofstream FileWrite;
	std::ifstream FileRead;

public:
	FileIO(std::string, std::string);
	//Open/Close file
	void OpenFile();
	void CloseFile();
	void ActorSheetLoad();
	int ReceiveInt(int);
	std::string ReceiveString(int);

};
