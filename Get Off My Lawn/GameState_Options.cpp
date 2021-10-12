/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_Options.cpp 
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Options
gamestate.
Functions include:
GameStateOptionsLoad
GameStateOptionsInit
GameStateOptionsUpdate
GameStateOptionsDraw
GameStateOptionsFree
GameStateOptionsUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_Options.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "Input.h"

// creating font

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateOptionsLoad(void)
{
	// Spawns all objects within the options menu
	Spawn_Object(OPTIONS_BACKGROUND, 0.0f, 0.0f); // spawns background image
	Spawn_Object(BACK_BUTTON, 550.0f, 250.0f);	  // spawns back button
	Spawn_Object(BGM_BUTTON, -300.0f, 50.0f);	  // spawns background image
	Spawn_Object(SFX_BUTTON, -300.0f, -50.0f);    // spawns background image
	Spawn_Object(INCREASE_VOLUME_BUTTON, 350.0f, 50.0f);   // BGM
	Spawn_Object(DECREASE_VOLUME_BUTTON, -150.0f, 50.0f);  // BGM
	Spawn_Object(VOLUME_BAR, 100.0f, 50.0f);			   // BGM
	Spawn_Object(INCREASE_VOLUME_BUTTON, 350.0f, -50.0f);  // SFX
	Spawn_Object(DECREASE_VOLUME_BUTTON, -150.0f, -50.0f); // SFX
	Spawn_Object(VOLUME_BAR, 100.0f, -50.0f);			   // SFX

	Spawn_Object(FULLSCREEN, -200.0f, -200.0f);		  // FULLSCREEN
	Spawn_Object(FULLSCREEN_BUTTON, 100.0f, -200.0f); // FULLSCREEN BUTTON
	
}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateOptionsInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateOptionsUpdate(void)
{
	logic_components.object_manager->Update_Objects(); //updates all objects
	Input_Handle_Options(); // input for all options

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
void GameStateOptionsDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects

	char strBuffer[1024]; //buffer to contain string
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//prints string
	sprintf_s(strBuffer, "CLICK BACKSPACE TO GO TO MAIN MENU");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)200, (f32)0, (f32)0, (f32)1);

}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateOptionsFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateOptionsUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}