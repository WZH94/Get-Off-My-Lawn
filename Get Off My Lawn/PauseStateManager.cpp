/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   PauseStateManager.cpp
\author Wong Zhihao
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the Pause State Manager, that is another game state
apart from the current Game State Manager that loops within the game loop.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PauseStateManager.h"	// Function and class declarations
#include "LogicComponents.h"	// Logic components
#include "GameStateList.h"		// Game state enums
#include "BlackScreen.h"		// Black screen class

// All the Pause States in the game
#include "PauseState_Fade.h"
#include "PauseState_Menu.h"
#include "PauseState_Victory.h"
#include "PauseState_Defeat.h"

/******************************************************************************/
/*!
Unload function within the pause loop, same for every pause state.
*/
/******************************************************************************/
void Pause_State_Manager::Pause_State_Unload(void)
{
	logic_components.object_manager->Free_Pause_Object_List();
}

/******************************************************************************/
/*!
Set the pause state manager to the inputted pause state
*/
/******************************************************************************/
void Pause_State_Manager::Set_Pause(PS_STATES state)
{
	// Assigns function pointers
	Assign_Pause_States(state);

	// Save the current game state
	gAEGameStateCurr_saved_ = gAEGameStateCurr;

	// Set it to this game state so it enters pause state loop
	gAEGameStateCurr = GS_PAUSE;

	next_pause_state_ = state;
}

/******************************************************************************/
/*!
Set the pause state manager to unpause and break out of pause loop
*/
/******************************************************************************/
void Pause_State_Manager::Set_Unpause()
{
	// Ensures saved current game state does not get overwritten.
	if (gAEGameStateCurr_saved_ != GS_PAUSE)
		gAEGameStateCurr = gAEGameStateCurr_saved_;

	else gAEGameStateCurr = 0xFFFFFF;

	next_pause_state_ = PAUSE_BLANK;
}

/******************************************************************************/
/*!
Assign function pointers to the various pause states
*/
/******************************************************************************/
void Pause_State_Manager::Assign_Pause_States(PS_STATES state)
{
	switch (state)
	{
	case PAUSE_MENU:
		Pause_State_Load = PauseStateMenu_Load;
		Pause_State_Update = PauseStateMenu_Update;
		Pause_State_Draw = PauseStateMenu_Draw;
		break;
	case PAUSE_FADE:
		Pause_State_Load = PauseStateFade_Load;
		Pause_State_Update = PauseStateFade_Update;
		Pause_State_Draw = PauseStateFade_Draw;
		break;
	case PAUSE_TUTORIAL:

		break;
	case PAUSE_VICTORY:
		Pause_State_Load = PauseStateVictory_Load;
		Pause_State_Update = PauseStateVictory_Update;
		Pause_State_Draw = PauseStateVictory_Draw;
		break;
	case PAUSE_DEFEAT:
		Pause_State_Load = PauseStateDefeat_Load;
		Pause_State_Update = PauseStateDefeat_Update;
		Pause_State_Draw = PauseStateDefeat_Draw;
		break;
	}
}

/******************************************************************************/
/*!
	Set the current pause state so that it loops as a pause loop
*/
/******************************************************************************/
void Pause_State_Manager::Set_Current_State()
{
	current_pause_state_ = next_pause_state_;
}

/******************************************************************************/
/*!
	Check if the current == next, same as the GameStateManager
*/
/******************************************************************************/
bool Pause_State_Manager::Check_Current_State()
{
	return current_pause_state_ == next_pause_state_ ? true : false;
}