#pragma once
#include "Actor.h";
#include <iostream>
#include <fstream>
#include <sstream>

class Director
{
private:
	int DirectorID;
	std::string DirectorSheet;
	std::string Directory;
	bool DirectorSleeping;
	std::string PushedInputRequest;
	Actor* PushRequestActor;
	//Actor Array
	std::vector<Actor> ActorList;
	int ActorListSize;

	//ActorLoacator
	int ActorLocator(int);

public:
	//Constructors
	Director();
	Director(std::string);
	Director(int);
	~Director();
	//Sleep states
	bool DirectorSleepState();
	void DirectorSleepSwitch();
	//Request Actor System [Only 1 actor can be requested at a time and used at a time. Directors can not recive if they are requesting and vice-versa]
	Actor* PushActorLoan(short int);
	void RequestActorLoan(Actor*);

	//Request
	//Request ID
	int RequestID();
	int RequestActorID(int);
	void RequestActorGFX(int, int*, float*, float*, float*);
	void RequestActorGFXList(int, int*);

	//Actor Controler
	//
	//Add Actor Hardcode (Debug)
	void AddActor(int, float, float, float, float, float, float, bool, bool, std::vector<unsigned int>);
	//Add Actor from SAS
	void AddActor(std::string);
	int RequestDirectorListSize();

	//ActorRequests
	//
	//Request Attribute
	int RequestActorAttribute(int, unsigned int);
	//Request Actor Position/Dimension
	float RequestActorPositionDimension(int, int);
	//Request Actor State
	bool RequestActorState(int);
	//Request Actor Collision Switch State
	bool RequestActorCollisionSwitchState(int);
	//Request Actor Render State
	bool RequestActorRenderState(int);

	//Actor Logic
	//
	//Add GFX ID to an actor
	void AssignGFXID(int, int, int);
	void DeAssignGFXID(int, int, int);
	//Change/Effect Actor Attributes
	void EffectActorAttribute(int, unsigned int, int);
	void ChangeActorAttribue(int, unsigned int, int);
	//Translate Actor
	// X = 1 | Y = -1 | Z = 0
	void TranslateActor(int, int, float);
	void TranslateActorFixed(int, float, float, float);
	//Actor States
	void ActivateActor(int);
	void DeActivateActor(int);
	//Collision switches
	void ActorCollisionSwitch(int);
	//Actor Render state switch
	void ActorRenderStateSwitch(int);
	//Actor Collision Detection
	//Check Collision with fixed values
	bool CheckActorCollisionFixed(int, float, float, float);
	bool CheckActorCollisionActor(int, int);
	bool CheckActorCollisionLoanActor(int, Actor*);

	//Kill Actor
	void KILLACTOR(int);
};