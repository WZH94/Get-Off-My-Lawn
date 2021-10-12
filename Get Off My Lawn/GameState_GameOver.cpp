/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_GameOver.cpp 
\author		Tan Zhi Quan, zhiquan.tan (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the GameOver
gamestate.
Functions include:
GameStateGameOverLoad
GameStateGameOverInit
GameStateGameOverUpdate
GameStateGameOverDraw
GameStateGameOverFree
GameStateGameOverUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_GameOver.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "LevelData.h"			// Enum for all levels

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateGameOverLoad(void)
{
	Spawn_Object(LEVEL1_BACKGROUND, 0.0f, 0.0f); // spawns background image
}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateGameOverInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateGameOverUpdate(void)
{
	logic_components.object_manager->Update_Objects(); //updates all objects

	//switches to main menu 
	if (AEInputCheckCurr(AEVK_BACK))
	{
		std::cout << "Going to main menu" << std::endl;
		gAEGameStateNext = GS_MAINMENU;
	}

	//switches to level select
	if (AEInputCheckCurr(AEVK_RETURN))
	{
		std::cout << "Going to level select" << std::endl;
		gAEGameStateNext = GS_LEVELSELECT;
	}
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateGameOverDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects

	char strBuffer[1024]; //buffer to contain string
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//prints string
	sprintf_s(strBuffer, "GAME OVER");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)250, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK BACKSPACE TO RETURN TO MAIN MENU");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)200, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK ENTER TO RETURN TO LEVEL SELECT");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)150, (f32)0, (f32)0, (f32)1);

}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateGameOverFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateGameOverUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}