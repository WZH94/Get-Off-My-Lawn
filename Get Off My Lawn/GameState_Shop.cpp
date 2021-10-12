/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_GameOver.cpp 
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Shop
gamestate.
Functions include:
GameStateShopLoad
GameStateShopInit
GameStateShopUpdate
GameStateShopDraw
GameStateShopFree
GameStateShopUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_Shop.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "PlayerData.h"			// Player stars
#include "Input.h"
#include "RenderManager.h"

// creating font

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateShopLoad(void)
{
	Spawn_Object(UPGRADE_BACKGROUND, 0.0f, 0.0f); // spawns background image

	Spawn_Object(BACK_BUTTON, 550.0f, 250.0f);			// spawns back button

	logic_components.level_data->Spawn_Upgrade_Panels();  // spawns button for shop
	logic_components.level_data->Spawn_Upgrade_Buttons(); // spawns button for shop


	Spawn_Object(GENERAL_STARS_LEFT, -450.0f, -250.0f);   // spawns number of stars the player has left

	system_components.audio_manager->Stream_Music(MUSIC_MAIN_MENU); //starts music
}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateShopInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateShopUpdate(void)
{
	logic_components.object_manager->Update_Objects(); //updates buttons and other objects
	Input_Handle_Shop(); //keyboard inputs for shop

	//switches to main menu 
	if (AEInputCheckReleased(AEVK_BACK))
	{
		std::cout << "Going to level select" << std::endl;
		gAEGameStateNext = GS_LEVELSELECT;
	}

	playdata.Open_Shop(); //functions for shop
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateShopDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects

	char strBuffer[1024]; //buffer to contain string
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//prints string
	sprintf_s(strBuffer, "THE SHOP");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)250, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK BACKSPACE TO GO TO LEVEL SELECT");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)200, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "%d", playdata.Get_Stars_Collected());
	Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, -414, -257);
}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateShopFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateShopUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}