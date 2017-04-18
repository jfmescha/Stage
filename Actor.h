#pragma once
#include <vector>

class Actor
{
	class Box
	{
	private:
		//Box Dimentions
		int BoxID;
		float Xpos, Ypos, Zpos;
		float Width, Height, Length;

	public:
		Box();
		Box(int, float, float, float, float, float, float);
		void CreateBox(int, float, float, float, float, float, float);
		~Box();
		//Return BoxID
		int returnBoxID();
		//Box Data returns
		// X = -1 | Y = -2 | Z = -3 | Width = 1 | Height = 2 | Length = 3
		float returnBox(int);
		void UpdateBox(float, float, float, float, float, float);

	};

	class ActorGFXObject
	{
	private:
		//Position Values
		float Xpos, Ypos, Zpos;
		int GFXID;
		int ObjectID;

	public:
		void CreateObject(int, float, float, float, int);
		int PushGFXID();
		int PushObjectID();
		// -1 = X | 0 = Y | 1 = Z
		float PushPos(int);

	};

private:
	//Actor Basic Values
	//IDS
	int ActorID;
	short int NodeID[256];
	short int GFXIDState;
	short int NodeIDState;
	std::vector<int> AnimationID;
	std::vector<ActorGFXObject> GFXObjectList;
	int GFXObjectListSize;
	int GFXObjectID;
	int GFXList[256];
	//Sheets
	std::string ActorSheet;
	//Values
	float Xpos, Ypos, Zpos;
	float Width, Height, Length;
	Box ActorBox;
	std::vector<unsigned int> ActorAttributes;
	//States
	bool Alive, Active;
	bool RenderStateSwitch;
	bool CollisionSwitch;

public:
	//Constructors
	//Defualt
	Actor();
	//FileIO Creation
	Actor(int, std::string);
	//Hardcode Creation
	//ID,X,Y,Z,W,H,L,Active,RenderState,Attributes
	Actor(int, float, float, float, float, float, float, bool, bool, std::vector<unsigned int>);
	~Actor();
	//Active switch / Death state
	bool ActorAlive();
	void ActorKill();
	bool ActorState();
	void ActorStateSwitch();
	void ActorCollisionSwitch();
	bool ActorCollisionSwitchState();

	//ActorID Push
	int PushActorID();

	//Translate actor
	// - Value (X = 1/ Y = -1/ Z = 0) , Ammount -
	void TranslateActor(int, float);
	void TranslateActorFixed(float, float, float);

	//Render
	int GFXObjectLocator(int);
	void RenderSwitch();
	bool RenderState();
	void AddGFXObject(int, float, float, float);
	void RemoveGFXObject(int);
	void PushGFXIDList(int*);
	int PushGFXObjectID(int);
	float PushGFXObjectCords(int, int);
	//Legacy
	void PushRenderList(int*);
	void UpdateRenderList(int, int, bool);
	// - chorio ID -
	// NOT INIT YET | void PlayAnimation(); |
	// NOT INIT YET | void PushNodeList(); |

	//ID Controllers
	void AddNodeID(int, int);
	void RemoveNodeID(int, int);

	//Attributes Controller;
	// - needed attribute ID -
	int PushActorAttribute(unsigned int);
	// - attribute , value -
	void UpdateActorAttribute(unsigned int, int);
	void ChangeActorAttribute(unsigned int, int);

	//Logic
	// Check collision between boxs.
	bool CollisionCheck(Box);
	bool CollisionCheck(float, float, float);
	bool CollisionCheck(float, float, float, float, float, float);
	Box PushActorBox();
	

};