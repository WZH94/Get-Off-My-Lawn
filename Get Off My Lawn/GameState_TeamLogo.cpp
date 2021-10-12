/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_TeamLogo.cpp 
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Team Logo
gamestate.
Functions include:
GameStateTeamLogoLoad
GameStateTeamLogoInit
GameStateTeamLogoUpdate
GameStateTeamLogoDraw
GameStateTeamLogoFree
GameStateTeamLogoUnload


Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_TeamLogo.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "Input.h"
#include "RenderManager.h"

// creating font

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
int logo_display_time_team = 0; //counter for how long the time will display
void GameStateTeamLogoLoad(void)
{

	Spawn_Object(TEAM_LOGO_BACKGROUND, 0.0f, 0.0f); // spawns background image

}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoInit(void)
{
	logic_components.object_manager->Initiate_Fade_Black_Screen(false); //starts fade on screen

	AEGfxSetBlendMode(AE_GFX_BM_BLEND); //blend for fade
}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoUpdate(void)
{
	logic_components.object_manager->Update_Objects(); //updates all objects

	++logo_display_time_team; //increases the counter for logo

	// Once time is hit, changes game state, starts the fade
	if (logo_display_time_team > 200)
	{
		gAEGameStateNext = GS_MAINMENU;
		logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
	}

	//switches to main menu 
	if (AEInputCheckReleased(AEVK_RBUTTON) || AEInputCheckReleased(AEVK_LBUTTON) || AEInputCheckReleased(AEVK_SPACE) || AEInputCheckReleased(AEVK_ESCAPE) || AEInputCheckReleased(AEVK_RETURN))
	{
		gAEGameStateNext = GS_MAINMENU;
	}

}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects
}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateTeamLogoUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}