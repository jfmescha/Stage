#include <string>
#include <iostream>
#include "Scene.h"
#include "StageTools.h"
#include "LITSoft.h"
#include "Puppeteer.h"
#include "FileIO.h"

int main(int argc, char *argv[])
{
	///Init Logic -> Render -> LogicData -> RenderData
	//Create a Puppeteer
	Puppeteer PuppetMaster;
	//Create game tick
	FPSTicker LogicTick(30);
	FPSTicker LITTick(0);
	//Create and Init Software window.
	int screenWidth = 1280;
	int screenHeight = 720;
	LIT SoftBox;
	SoftBox.InitSoftware(screenWidth, screenHeight);

	GraphicsObject TestObject(0);
	TestObject.LoadGraphicObject("Sprites/logo.png",SoftBox.PushRenderer());

	Scene TestScene("Sets/TestScene.scn");
	TestScene.LoadScene();

	//Player Init
	//Director Player(1);
	//Player.AddActor("Sheets/Directors/ActorSheets/PlayerBase.sas");
	//Director EnemyDirector("Sheets/Directors/TestDirector.sdd");
	//EnemyDirector.TranslateActor(2, 1, 40);
	//EnemyDirector.TranslateActor(3, 1, 80);
	//EnemyDirector.TranslateActor(4, 1, 120);
	//EnemyDirector.TranslateActor(5, 1, 160);
	//EnemyDirector.TranslateActor(6, 1, 200);
	//EnemyDirector.TranslateActor(7, 1, 240);
	//EnemyDirector.TranslateActor(8, 1, 280);

	//Play
	while (!PuppetMaster.Quit())
	{
		PuppetMaster.Perform();
		//Logic
		if (LogicTick.TickCheck())
		{
			
			///Update tick
			LogicTick.UpdateTick();
		}
		//Render
		if (LITTick.TickCheck())
		{
			///Update
			SoftBox.RenderUpdateSoft();

			///Renderfield START
			
			///Renderfeild END

			//Verson
			SoftBox.DrawSoftText(screenWidth - 20, 1, 255, 255, 255, std::to_string(LITTick.PushFPS()));
			TestObject.DrawGraphicObject(SoftBox.PushRenderer(), 0, 0, 0, 60, 16, 0);
			SoftBox.DrawSoftText(590, 1, 255, 255, 255, "Pre-Alpha");
			//SoftBox.DrawSoftText(screenWidth - 220, 1, 255, 255, 255, "Player| X: " + std::to_string(Player.RequestActorPositionDimension(1, -1)) + " Y: " + std::to_string(Player.RequestActorPositionDimension(1, -2)));
			//SoftBox.DrawSoftText(screenWidth - 350, 1, 255, 255, 255, "Mouse| X: " + std::to_string(PuppetMaster.GetMouseX()) + " Y: " + std::to_string(PuppetMaster.GetMouseY()));

			///Render
			SoftBox.RenderSoftware();
			///Update tick
			LITTick.UpdateTick();
		}
	}

	SoftBox.CloseSoftware();
	return 0;
}