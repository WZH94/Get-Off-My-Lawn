/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   PauseStateManager.h
\author Wong Zhihao
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of the Pause State Manager class and
its functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef PAUSESTATEMANAGER_H
#define PAUSESTATEMANAGER_H

// All the pause states in the game
enum PS_STATES
{
	PAUSE_MENU = 0,
	
	PAUSE_FADE,
	PAUSE_TUTORIAL,
	PAUSE_VICTORY,
	PAUSE_DEFEAT,

	PAUSE_BLANK,
};

class Pause_State_Manager
{
protected:
	// Used to keep the pause loop
	PS_STATES current_pause_state_;
	PS_STATES next_pause_state_;

	// Store the current game state when pausing
	unsigned gAEGameStateCurr_saved_;

public:

	// Function pointers for the pause states
	void(*Pause_State_Load)(void);
	void(*Pause_State_Update)(void);
	void(*Pause_State_Draw)(void);

	// Unload function within the pause loop, same for every pause state.
	void Pause_State_Unload (void);

	// Set the pause state manager to the inputted pause state
	void Set_Pause(PS_STATES);

	// Set the pause state manager to unpause and break out of pause loop
	void Set_Unpause();

	// Assign function pointers to the various pause states
	void Assign_Pause_States(PS_STATES);

	// Set the current pause state so that it loops as a pause loop
	void Set_Current_State();

	// Check if the current pause state is equal to next pause state and returns accordingly.
	// Use for changing between pause states when already inside a pause state
	bool Check_Current_State();
};



#endif