#include "Actor.h"

Actor::Box::Box(int id, float x, float y, float z, float w , float h, float l)
{
	BoxID = id;
	Xpos = x;
	Ypos = y;
	Zpos = z;
	Width = w;
	Height = h;
	Length = l;
}
void Actor::Box::CreateBox(int id, float x, float y, float z, float w, float h, float l)
{
	BoxID = id;
	Xpos = x;
	Ypos = y;
	Zpos = z;
	Width = w;
	Height = h;
	Length = l;
}

Actor::Box::Box()
{}

Actor::Box::~Box()
{
	BoxID = 0;
	Xpos = 0.0f;
	Ypos = 0.0f;
	Zpos = 0.0f;
	Width = 0.0f;
	Height = 0.0f;
	Length = 0.0f;
}

int Actor::Box::returnBoxID()
{
	return BoxID;
}

float Actor::Box::returnBox(int selector)
{
	if (selector == -1)
		return Xpos;
	if (selector == -2)
		return Ypos;
	if (selector == -3)
		return Zpos;
	if (selector == 1)
		return Width;
	if (selector == 2)
		return Height;
	if (selector == 3)
		return Length;
	else
		return 0.0f;
}

void Actor::Box::UpdateBox(float x, float y, float z, float w, float h, float l)
{
	Xpos = x;
	Ypos = y;
	Zpos = z;
	Width = w;
	Height = h;
	Length = l;
}

Actor::Actor()
{
	for (int i = 0; i < 256; i++)
		GFXList[i] = 0;
	GFXObjectListSize = 0;
	GFXObjectID = 0;
}

Actor::Actor(int newactorid, std::string sheetname)
{
	ActorID = newactorid;
	ActorSheet = sheetname;
	for (int i = 0; i < 256; i++)
		GFXList[i] = 0;
	GFXObjectListSize = 0;
	GFXObjectID = 0;
}

Actor::Actor(int tID, float tX, float tY, float tZ, float tW, float tH, float tL, bool tActive, bool tRenderS, std::vector<unsigned int> tAtbs)
{
	ActorID = tID;
	Xpos = tX;
	Ypos = tY;
	Zpos = tZ;
	Width = tW;
	Height = tH;
	Length = tL;
	Active = tActive;
	RenderStateSwitch = tRenderS;
	ActorAttributes.resize(tAtbs.size());
	for (int i = 0; i < tAtbs.size(); i++)
	{
		ActorAttributes[i] = tAtbs[i];
	}
	ActorBox.CreateBox(0, Xpos, Ypos, Zpos, Width, Height, Length);

	CollisionSwitch = true;

	for (int i = 0; i < 256; i++)
		GFXList[i] = 0;

	GFXObjectListSize = 0;
	GFXObjectID = 0;
}

Actor::~Actor()
{
	ActorBox.~Box();
	AnimationID.clear();
	ActorAttributes.clear();
	GFXObjectList.clear();
}

bool Actor::ActorAlive()
{
	return Alive;
}

void Actor::ActorKill()
{
	if (Alive)
		Alive = false;
}

bool Actor::ActorState()
{
	return Active;
}

void Actor::ActorStateSwitch()
{
	if (Active)
		Active = false;
	else
		Active = true;
}

void Actor::ActorCollisionSwitch()
{
	if (CollisionSwitch)
		CollisionSwitch = false;
	else
		CollisionSwitch = true;
}

bool Actor::ActorCollisionSwitchState()
{
	return CollisionSwitch;
}

int Actor::PushActorID()
{
	return ActorID;
}

void Actor::TranslateActor(int valuechange, float ammount)
{
	//X
	if(valuechange == 1)
	{
		Xpos += ammount;
	}
	//Y
	else if(valuechange == -1)
	{
		Ypos += ammount;
	}
	//Z
	else if (valuechange == 0)
	{
		Zpos += ammount;
	}
	ActorBox.UpdateBox(Xpos, Ypos, Zpos, Width, Height, Length);
}

void Actor::TranslateActorFixed(float x, float y, float z)
{
	Xpos = x;
	Ypos = y;
	Zpos = z;
	ActorBox.UpdateBox(Xpos, Ypos, Zpos, Width, Height, Length);
}

int Actor::GFXObjectLocator(int id)
{
	for (int i = 0; i < GFXObjectList.size(); i++)
	{
		if (GFXObjectList[i].PushObjectID() == id)
			return i;
	}
	return 0;
}

void Actor::RenderSwitch()
{
	if (RenderStateSwitch == true)
		RenderStateSwitch = false;
	else
		RenderStateSwitch = true;
}

bool Actor::RenderState()
{
	return RenderStateSwitch;
}

void Actor::AddGFXObject(int id, float tx, float ty, float tz)
{
	GFXObjectListSize++;
	GFXObjectID++;
	GFXObjectList.resize(GFXObjectListSize);
	GFXObjectList[GFXObjectListSize - 1].CreateObject(id, tz, ty, tz, GFXObjectID);
}

void Actor::RemoveGFXObject(int removecode)
{
	if (removecode <= GFXObjectListSize)
	{
		GFXObjectList.erase(GFXObjectList.begin() + (removecode-1));
		GFXObjectListSize--;
	}
}

void Actor::PushGFXIDList(int *list)
{
	//const int tempsize = (GFXObjectListSize-1);
	//int * templist = new int[tempsize];
	//for (int i = 0; i < tempsize; i++)
	//{
	//	templist[i] = GFXObjectList[i].PushObjectID();
	//}
	//list = templist;
}

int Actor::PushGFXObjectID(int id)
{
	return GFXObjectList[GFXObjectLocator(id)].PushGFXID();
}

float Actor::PushGFXObjectCords(int id, int pos)
{
	switch (pos)
	{
	case -1: return GFXObjectList[GFXObjectLocator(id)].PushPos(-1);
	case 0: return GFXObjectList[GFXObjectLocator(id)].PushPos(0);
	case 1: return GFXObjectList[GFXObjectLocator(id)].PushPos(1);
	}
}

void Actor::PushRenderList(int *pusher)
{
	for(int i = 0; i < 256; i++)
		pusher[i] = GFXList[i];
}

void Actor::UpdateRenderList(int gfxID, int pos, bool updater)
{
	if(updater)
		GFXList[pos] = gfxID;
	if (!updater)
		GFXList[pos] = 0;
}

int Actor::PushActorAttribute(unsigned int neededatt)
{
	if (neededatt >= ActorAttributes.size())
		neededatt = 0;
	return ActorAttributes[neededatt];
}

void Actor::UpdateActorAttribute(unsigned int att, int value)
{
	ActorAttributes[att] += value;
}

void Actor::ChangeActorAttribute(unsigned int att, int value)
{
	ActorAttributes[att] = value;
}

bool Actor::CollisionCheck(Box checkie)
{
	if (
		(ActorBox.returnBox(-1) >= checkie.returnBox(-1) && ActorBox.returnBox(-1) <= (checkie.returnBox(-1) + checkie.returnBox(1))
		||
		(ActorBox.returnBox(-1)+ActorBox.returnBox(1)) >= checkie.returnBox(-1) && (ActorBox.returnBox(-1) + ActorBox.returnBox(1)) <= (checkie.returnBox(-1) + checkie.returnBox(1)))
		&&
		(ActorBox.returnBox(-2) >= checkie.returnBox(-2) && ActorBox.returnBox(-2) <= (checkie.returnBox(-2) + checkie.returnBox(2))
		||
		(ActorBox.returnBox(-2) + ActorBox.returnBox(2)) >= checkie.returnBox(-2) && (ActorBox.returnBox(-2) + ActorBox.returnBox(2)) <= (checkie.returnBox(-2) + checkie.returnBox(2)))
		&&
		ActorBox.returnBox(-3) >= checkie.returnBox(-3) && ActorBox.returnBox(-3) <= (checkie.returnBox(-3) + checkie.returnBox(3))
		&&
		CollisionSwitch == true
	   )
	{
		return true;
	}
	else
		return false;
}

bool Actor::CollisionCheck(float fixposX, float fixposY, float fixposZ)
{
	if (
		fixposX >= ActorBox.returnBox(-1) && fixposX <= (ActorBox.returnBox(-1) + ActorBox.returnBox(1))
		&&
		fixposY >= ActorBox.returnBox(-2) && fixposY <= (ActorBox.returnBox(-2) + ActorBox.returnBox(2))
		&&
		fixposZ >= ActorBox.returnBox(-3) && fixposZ <= (ActorBox.returnBox(-3) + ActorBox.returnBox(3))
		&&
		CollisionSwitch == true
		)
	{
		return true;
	}
	else
		return false;
}

bool Actor::CollisionCheck(float fixposX, float fixposY, float fixposZ, float fixposWidth, float fixposHeight, float fixposLength)
{
	if (
		ActorBox.returnBox(-1) >= fixposX && ActorBox.returnBox(-1) <= (fixposX + fixposWidth)
		&&
		ActorBox.returnBox(-2) >= fixposY && ActorBox.returnBox(-2) <= (fixposY + fixposHeight)
		&&
		ActorBox.returnBox(-3) >= fixposZ && ActorBox.returnBox(-3) <= (fixposZ + fixposLength)
		&&
		CollisionSwitch == true
		)
	{
		return true;
	}
	else
		return false;
}

Actor::Box Actor::PushActorBox()
{
	return ActorBox;
}

void Actor::AddNodeID(int desID, int addedID)
{
	if (NodeIDState < 256)
	{
		NodeID[desID] = addedID;
		NodeIDState++;
	}
	else
		NodeIDState = 256;
}

void Actor::RemoveNodeID(int desID, int valueID)
{
	NodeID[desID] = 0;
	NodeIDState--;
	if (NodeIDState < 0)
		NodeIDState = 0;
}

void Actor::ActorGFXObject::CreateObject(int id, float tx, float ty, float tz, int oid)
{
	GFXID = id;
	ObjectID = oid;
	Xpos = tx;
	Ypos = ty;
	Zpos = tz;
}

int Actor::ActorGFXObject::PushObjectID()
{
	return ObjectID;
}

int Actor::ActorGFXObject::PushGFXID()
{
	return GFXID;
}

float Actor::ActorGFXObject::PushPos(int selector)
{
	switch (selector)
	{
	case -1: return Xpos;
	case 0: return Ypos;
	case 1: return Zpos;
	}
}
