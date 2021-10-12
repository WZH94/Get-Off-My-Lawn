/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_LoadPlayer.cpp 
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Load Player
gamestate.
Functions include:
GameStateLoadPlayerLoad
GameStateLoadPlayerInit
GameStateLoadPlayerUpdate
GameStateLoadPlayerDraw
GameStateLoadPlayerFree
GameStateLoadPlayerUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_LoadPlayer.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "PlayerData.h"			// For player saves
#include "Input.h"
#include <string>

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerLoad(void)
{
	// Spawns background
	Spawn_Object(MAIN_MENU_BACKGROUND, 0.0f, 0.0f); // spawns background image
	Spawn_Object(BACK_BUTTON, 550.0f, 250.0f);			// spawns back button

	//Spawn_Object(NEW_GAME, -350.0f, -100.0f);
	//Spawn_Object(NEW_GAME, 0.0f, -100.0f);
	//Spawn_Object(NEW_GAME, 350.0f, -100.0f);

	logic_components.level_data->Spawn_Level_Play_Data();

}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerUpdate(void)
{
	logic_components.object_manager->Update_Objects();

	Input_Handle_Load_Player();
	//switches to main menu 
	if (AEInputCheckTriggered(AEVK_BACK))
	{
		std::cout << "Going to main menu" << std::endl;
		gAEGameStateNext = GS_MAINMENU;
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		gAEGameStateNext = AE_GS_QUIT;

	if (AEInputCheckTriggered(AEVK_RETURN))
	{
		std::cout << "Going to Level Select" << std::endl;
		gAEGameStateNext = GS_LEVELSELECT;
	}


	/* Following keys make save files*/
	if (AEInputCheckReleased(AEVK_1))
	{
		std::cout << "make new player save" << std::endl;
		playdata.Close_Current_Open_File();
		playdata.Make_New_Save(1);
		gAEGameStateNext = GS_LEVELSELECT;
	}

	if (AEInputCheckReleased(AEVK_2))
	{
		std::cout << "make new player save" << std::endl;
		playdata.Close_Current_Open_File();
		playdata.Make_New_Save(2);
		gAEGameStateNext = GS_LEVELSELECT;
	}

	if (AEInputCheckReleased(AEVK_3))
	{
		std::cout << "make new player save" << std::endl;
		playdata.Close_Current_Open_File();
		playdata.Make_New_Save(3);
		gAEGameStateNext = GS_LEVELSELECT;
	}

	/* Following keys delete save files*/
	if (AEInputCheckReleased(AEVK_7))
	{
		std::string delete1 = playdata.Get_Path_Name() + "\\playerdata1.txt";
		playdata.Delete_Save(delete1);
	}

	if (AEInputCheckReleased(AEVK_8))
	{
		std::string delete2 = playdata.Get_Path_Name() + "\\playerdata2.txt";
		playdata.Delete_Save(delete2);
	}

	if (AEInputCheckReleased(AEVK_9))
	{
		std::string delete3 = playdata.Get_Path_Name() + "\\playerdata3.txt";
		playdata.Delete_Save(delete3);
	}
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects

	char strBuffer[1024]; //buffer to contain string
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//prints string
	sprintf_s(strBuffer, "LEVEL SELECT");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)250, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK BACKSPACE TO GO TO MAIN MENU");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)200, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK ENTER TO GO TO LEVEL SELECT");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)150, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK 1 TO CREATE PLAYER");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)100, (f32)0, (f32)0, (f32)1);
	
	playdata.Print_Player_Save_Stats();
}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateLoadPlayerUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}