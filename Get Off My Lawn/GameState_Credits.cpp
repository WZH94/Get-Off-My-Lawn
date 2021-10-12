/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_Credits.cpp 
\author		Tan Zhi Quan, zhiquan.tan (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Credits
gamestate.
Functions include:
GameStateCreditsLoad
GameStateCreditsInit
GameStateCreditsUpdate
GameStateCreditsDraw
GameStateCreditsFree
GameStateCreditsUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_Credits.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "Input.h"

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateCreditsLoad(void)
{
	Spawn_Object(CREDITS_BACKGROUND, 0.0f, 0.0f); // spawns background image
	Spawn_Object(BACK_BUTTON, 550.0f, 250.0f);	  // spawns back button
}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateCreditsInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateCreditsUpdate(void)
{
	logic_components.object_manager->Update_Objects();  // updates all objects
	Input_Handle_Credits();								// input for credits

	//switches to main menu 
	if (AEInputCheckReleased(AEVK_BACK))
	{
		std::cout << "Going to Main Menu" << std::endl;
		gAEGameStateNext = GS_MAINMENU;
	}
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateCreditsDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects

	char strBuffer[1024]; //buffer to contain string
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//prints string
	sprintf_s(strBuffer, "CLICK BACKSPACE TO GO TO MAIN MENU");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)200, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "REMEMBER CREDIT FMOD");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_DEBUGGING_TEXT), (s8*)strBuffer, (s32)0, (s32)0, (f32)0, (f32)0, (f32)1);
}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateCreditsFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateCreditsUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}