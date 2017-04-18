#include "Director.h"

Director::Director()
{
	ActorListSize = 0;
}

Director::Director(std::string directory)
{
	std::ifstream FileRead;
	FileRead.open(directory, std::ifstream::in);
	std::string parser = "NULL";

	int line = 0;
	while (FileRead.eof() != true)
	{
		std::getline(FileRead, parser);
		if (line != 0)
			AddActor("Sheets/Directors/ActorSheets/"+parser);

		if (parser.find(':') != std::string::npos)
		{
			std::size_t posS = parser.find("(");
			std::size_t posE = parser.find(")");
			std::string tempS = parser.substr(posS + 1, posE - posS - 1);
			DirectorID = std::stoi(tempS);
			line++;
		}
	}
}

Director::Director(int id)
{
	DirectorID = id;
	ActorListSize = 0;
}

Director::~Director()
{
	ActorList.clear();
}

bool Director::DirectorSleepState()
{
	return DirectorSleeping;
}

void Director::DirectorSleepSwitch()
{
	if (DirectorSleeping == true)
		DirectorSleeping = false;
	else
		DirectorSleeping = true;
}

Actor* Director::PushActorLoan(short int actorrequest)
{
	if (actorrequest > ActorList.size() || actorrequest < 0)
		return &ActorList[0];
	else
		return &ActorList[ActorLocator(actorrequest)];
}

void Director::RequestActorLoan(Actor* requestactor)
{
	PushRequestActor = requestactor;
}

int Director::ActorLocator(int id)
{
	for (int i = 0; i < ActorList.size(); i++)
	{
		if (ActorList[i].PushActorID() == id)
			return i;
	}
	return 0;
}

int Director::RequestID()
{
	return DirectorID;
}

int Director::RequestActorID(int id)
{
	return ActorList[ActorLocator(id)].PushActorID();
}

void Director::RequestActorGFX(int id, int *gfxid, float *xpos, float *ypos, float *zpos)
{
	//ActorList[ActorLocator(id)].p
}

void Director::RequestActorGFXList(int id, int *tpusher)
{
	ActorList[ActorLocator(id)].PushRenderList(tpusher);
}

int Director::RequestActorAttribute(int id, unsigned int att)
{
	return ActorList[ActorLocator(id)].PushActorAttribute(att);
}

float Director::RequestActorPositionDimension(int id, int posvalue)
{
	return ActorList[ActorLocator(id)].PushActorBox().returnBox(posvalue);
}

bool Director::RequestActorState(int id)
{
	return ActorList[ActorLocator(id)].ActorState();
}

void Director::AssignGFXID(int id, int pos, int gfxid)
{
	ActorList[ActorLocator(id)].UpdateRenderList(gfxid, pos, true);
}

void Director::DeAssignGFXID(int id, int pos, int gfxid)
{
	ActorList[ActorLocator(id)].UpdateRenderList(gfxid, pos, false);
}

void Director::EffectActorAttribute(int id, unsigned int att, int value)
{
	ActorList[ActorLocator(id)].UpdateActorAttribute(att, value);
}

void Director::ChangeActorAttribue(int id, unsigned int att, int value)
{
	ActorList[ActorLocator(id)].ChangeActorAttribute(att, value);
}

void Director::AddActor(int ID, float x, float y, float z, float w, float h, float l, bool active, bool renders, std::vector<unsigned int> att)
{
	ActorListSize++;
	ActorList.resize(ActorListSize);
	Actor tempActor(ID, x, y, z, w, h, l, active, renders , att);
	ActorList[ActorListSize-1] = tempActor;
}

void Director::AddActor(std::string filename)
{
	std::ifstream ActorFileRead;

	int line = 0;

	int value = 0;
	bool sizeGiven = false;
	std::vector<unsigned int> AttributeSheet;
	int tID;
	float tX, tY, tZ, tW, tH, tL;
	bool tAct, tGA;

	ActorFileRead.open(filename, std::ifstream::in);
	std::string parser = "NULL";

	while (ActorFileRead.eof() != true)
	{
		line++;
		std::getline(ActorFileRead, parser, ',');

		if (parser.find(':') != std::string::npos)
		{
			std::size_t posS = parser.find("(");
			std::size_t posE = parser.find(")");
			std::string tempS = parser.substr(posS + 1, posE - posS - 1);
			switch (line)
			{
			case 1:
				tID = std::stoi(tempS);
				break;
			case 2:
				tX = std::stoi(tempS);
				break;
			case 3:
				tY = std::stoi(tempS);
				break;
			case 4:
				tZ = std::stoi(tempS);
				break;
			case 5:
				tW = std::stoi(tempS);
				break;
			case 6:
				tH = std::stoi(tempS);
				break;
			case 7:
				tL = std::stoi(tempS);
				break;
			case 8:
				tAct = std::stoi(tempS);
				break;
			case 9:
				tGA = std::stoi(tempS);
				break;
			}
			if (sizeGiven)
			{
				AttributeSheet[value] = std::stoi(tempS);
				value++;
			}

		}
		if (parser.find('$') != std::string::npos)
		{
			std::size_t posS = parser.find("(");
			std::size_t posE = parser.find(")");
			std::string tempS = parser.substr(posS + 1, posE - posS - 1);
			sizeGiven = true;
			AttributeSheet.resize(std::stoi(tempS));
		}

	}

	ActorFileRead.close();

	ActorListSize++;
	ActorList.resize(ActorListSize);
	Actor tempActor(ActorListSize, tX, tY, tZ, tW, tH, tL, tAct, tGA, AttributeSheet);
	ActorList[ActorListSize - 1] = tempActor;
}

int Director::RequestDirectorListSize()
{
	return ActorListSize;
}

void Director::TranslateActor(int id, int value, float amt)
{
	ActorList[ActorLocator(id)].TranslateActor(value, amt);
}

void Director::TranslateActorFixed(int id, float x, float y, float z)
{
	ActorList[ActorLocator(id)].TranslateActorFixed(x,y,z);
}

void Director::ActivateActor(int id)
{
	if (ActorList[ActorLocator(id)].ActorState() == false)
		ActorList[ActorLocator(id)].ActorStateSwitch();
}

void Director::DeActivateActor(int id)
{
	if (ActorList[ActorLocator(id)].ActorState() == true)
		ActorList[ActorLocator(id)].ActorStateSwitch();
}

void Director::ActorCollisionSwitch(int id)
{
	ActorList[ActorLocator(id)].ActorCollisionSwitch();
}

void Director::ActorRenderStateSwitch(int id)
{
	ActorList[ActorLocator(id)].RenderSwitch();
}

bool Director::RequestActorCollisionSwitchState(int id)
{
	return ActorList[ActorLocator(id)].ActorCollisionSwitchState();
}

bool Director::RequestActorRenderState(int id)
{
	return ActorList[ActorLocator(id)].RenderState();
}

bool Director::CheckActorCollisionFixed(int id, float fixposX, float fixposY, float fixposZ)
{
	return ActorList[ActorLocator(id)].CollisionCheck(fixposX, fixposY, fixposZ);
}

bool Director::CheckActorCollisionActor(int id, int id2)
{
	return ActorList[ActorLocator(id)].CollisionCheck(ActorList[ActorLocator(id2)].PushActorBox());
}

bool Director::CheckActorCollisionLoanActor(int id, Actor* tempactor)
{
	return ActorList[ActorLocator(id)].CollisionCheck(tempactor->PushActorBox());
}

void Director::KILLACTOR(int id)
{
	ActorList[ActorLocator(id)].ActorKill();
}
